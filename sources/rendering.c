/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egatien <egatien@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 23:04:35 by egibeaux          #+#    #+#             */
/*   Updated: 2025/09/24 00:57:51 by egibeaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	put_pixel(t_img *data, int x, int y, int color)
{
	int	pixel;

	pixel = y * (data->size_line / 4) + x;
	if (pixel > (SCREEN_HEIGHT * SCREEN_WIDTH))
		return ;
	data->address[pixel] = color;
}

void	drawline(int x, int start, int end, t_data *args)
{
	int			i;

	i = 0;
	while (i != start)
	{
		put_pixel(args->img_data, x, i, args->text->ceiling_color);
		i++;
	}
	while (i != end)
	{
		i++;
	}
	while (i != SCREEN_HEIGHT)
	{
		put_pixel(args->img_data, x, i, args->text->floor_color);
		i++;
	}
}

static void checkside (t_player *player_data)
{
	if (player_data->raydir_x < 0)
	{
		player_data->step_x = -1;
		player_data->side_dist_x = (player_data->pos_x - player_data->map_x)
			* player_data->delta_dist_x;
	}
	else
	{
		player_data->step_x = 1;
		player_data->side_dist_x = (player_data->map_x + 1.0 - player_data->pos_x)
			* player_data->delta_dist_x;
	}
	if (player_data->raydir_y < 0)
	{
		player_data->step_y = -1;
		player_data->side_dist_y = (player_data->pos_y - player_data->map_y)
			* player_data->delta_dist_y;
	}
	else
	{
		player_data->step_y = 1;
		player_data->side_dist_y = (player_data->map_y + 1.0 - player_data->pos_y) 
			* player_data->delta_dist_y;
	}
}

static void find_wall(t_data *args, t_player *player_data, int hit)
{
	hit = 0;

	while (args->map[player_data->map_y] && args->map[player_data->map_y][player_data->map_x] && hit == 0)
	{
		if (player_data->side_dist_x < player_data->side_dist_y)
		{
			player_data->side_dist_x += player_data->delta_dist_x;
			player_data->map_x += player_data->step_x;
			player_data->side = 0;
		}
		else
		{
			player_data->side_dist_y += player_data->delta_dist_y;
			player_data->map_y += player_data->step_y;
			player_data->side = 1;
		}
		if (args->map[player_data->map_y][player_data->map_x] == '1')
			hit = 1;
	}
	if (player_data->side == 0)
		player_data->perp_wall_dist = (player_data->side_dist_x - player_data->delta_dist_x);
	else
		player_data->perp_wall_dist = (player_data->side_dist_y - player_data->delta_dist_y);
	player_data->lineheight = (int) (SCREEN_HEIGHT / player_data->perp_wall_dist);
	player_data->drawstart = (player_data->lineheight * -1) / 2 + SCREEN_HEIGHT / 2;
}

void	setdata(t_player *player_data, int index)
{
	player_data->camera_x = 2 * index / (double) SCREEN_WIDTH - 1;
	player_data->raydir_x = player_data->dir_x + player_data->plane_x * player_data->camera_x;
	player_data->raydir_y = player_data->dir_y + player_data->plane_y * player_data->camera_x;
	if (player_data->raydir_x == 0)
		player_data->delta_dist_x = 1e30;
	else
	 	player_data->delta_dist_x = fabs(1 / player_data->raydir_x);
	if (player_data->raydir_y == 0)
		player_data->delta_dist_y = 1e30;
	else
		player_data->delta_dist_y =  fabs(1 / player_data->raydir_y);

	player_data->map_x = (int) player_data->pos_x;
	player_data->map_y = (int) player_data->pos_y;
}

t_img	*select_text(t_player *player_data, t_data *args)
{
	t_img	*temp;

	temp = NULL;
	if (player_data->side == 0)
	{
		if (player_data->raydir_x > 0)
			temp = args->wall_text[2];
		else
			temp = args->wall_text[3];
	}
	else
	{
		if (player_data->raydir_y > 0)
			temp = args->wall_text[1];
		else
			temp = args->wall_text[0];
	}
	return (temp);
}

void	func(t_player *player_data)
{
 	if (player_data->side == 0)
 		player_data->wall_x = player_data->pos_y + player_data->perp_wall_dist * player_data->raydir_y;
 	else
 		player_data->wall_x = player_data->pos_x + player_data->perp_wall_dist * player_data->raydir_x;
 	player_data->wall_x -= floor(player_data->wall_x);
 	player_data->tex_x = (int) (player_data->wall_x * 64.0);
 	if (player_data->side == 0 && player_data->raydir_x > 0)
 		player_data->tex_x = 64 - player_data->tex_x - 1;
	if (player_data->side == 1 && player_data->raydir_y < 0)
		player_data->tex_x = 64 - player_data->tex_x - 1;
}

void	draw_to_screen(int i, t_data *args, t_player *player_data, t_img *temp)
{
	int	j;

	j = player_data->drawstart;
	while (j < player_data->drawend)
	{
		player_data->tex_y = (int) player_data->tex_pos & (64 - 1);
		player_data->tex_pos += player_data->step;
		put_pixel(args->img_data, i, j, temp->address[64 * player_data->tex_y + player_data->tex_x]);
		j++;
	}
	drawline(i, player_data->drawstart, player_data->drawend, args);
	mlx_put_image_to_window(args->mlx,
		args->mlx_win, args->img_data->img, 0, 0);
}

//int	domath(void *data)
//{
//	int		i;
//	int		hit;
//	double	time = 0;	// for testing only remove when pusing
//	double	oldTime = 0;// same here 
//	t_data	*args;
//	t_img	*temp;
//
//	i = 0;
//	hit = 0;
//	temp = NULL;
//	args = (t_data *) data;
//	while (i < SCREEN_WIDTH)
//	{
//		oldTime = time;
//		time = getTicks();
//		printf("fps -> %f\n", (time - oldTime) / 1000.0);
//		setdata(args->player, i);
//		checkside(args->player);
//		find_wall(args, args->player, hit);
//		temp = select_text(args->player, args);
//		if (args->player->drawstart < 0)
//			args->player->drawstart = 0;
//		args->player->drawend = args->player->lineheight / 2 + SCREEN_HEIGHT / 2;
//		if (args->player->drawend >= SCREEN_HEIGHT)
//			args->player->drawend = SCREEN_HEIGHT - 1;
//		func(args->player);
//		args->player->step = 1.0 * 64.0 / args->player->lineheight;
//		args->player->tex_pos = (args->player->drawstart - SCREEN_HEIGHT / 2 + args->player->lineheight / 2) * args->player->step;
//		draw_to_screen(i, args, args->player, temp);
//		i++;
//	}
//	return (1);
//}
//



int domath(void *data)
{
    static double oldTime_ms = 0;   // persists between frames
    double        time_ms;
    int           i = 0;
    int           hit = 0;
    t_data        *args = (t_data *)data;
    t_img         *temp = NULL;
    struct timespec ts;

    // get current time at start of frame
    clock_gettime(CLOCK_MONOTONIC, &ts);
    time_ms = ts.tv_sec * 1000.0 + ts.tv_nsec / 1.0e6;

    // --- drawing loop ---
    while (i < SCREEN_WIDTH)
    {
        setdata(args->player, i);
        checkside(args->player);
        find_wall(args, args->player, hit);
        temp = select_text(args->player, args);
        if (args->player->drawstart < 0)
            args->player->drawstart = 0;
        args->player->drawend = args->player->lineheight / 2 + SCREEN_HEIGHT / 2;
        if (args->player->drawend >= SCREEN_HEIGHT)
            args->player->drawend = SCREEN_HEIGHT - 1;
        func(args->player);
        args->player->step = 64.0 / args->player->lineheight;
        args->player->tex_pos = (args->player->drawstart - SCREEN_HEIGHT / 2
            + args->player->lineheight / 2) * args->player->step;
        draw_to_screen(i, args, args->player, temp);
        i++;
    }

    // print FPS once per frame
    if (oldTime_ms > 0) {
        double frameTime = time_ms - oldTime_ms;
        printf("FPS: %.2f\n", 1000.0 / frameTime);
    }
    oldTime_ms = time_ms;

    return (1);
}
