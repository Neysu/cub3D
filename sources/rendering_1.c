/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egatien <egatien@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 13:23:19 by egatien           #+#    #+#             */
/*   Updated: 2025/10/27 13:24:01 by egatien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	setdata(t_player *player_data, int index)
{
	player_data->camera_x = 2 * index / (double) SCREEN_WIDTH - 1;
	player_data->raydir_x = player_data->dir_x
		+ player_data->plane_x * player_data->camera_x;
	player_data->raydir_y = player_data->dir_y
		+ player_data->plane_y * player_data->camera_x;
	if (player_data->raydir_x == 0)
		player_data->delta_dist_x = 1e30;
	else
		player_data->delta_dist_x = fabs(1 / player_data->raydir_x);
	if (player_data->raydir_y == 0)
		player_data->delta_dist_y = 1e30;
	else
		player_data->delta_dist_y = fabs(1 / player_data->raydir_y);
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
	if (player_data->drawstart < 0)
		player_data->drawstart = 0;
	player_data->drawend = player_data->lineheight / 2 + SCREEN_HEIGHT / 2;
	if (player_data->drawend >= SCREEN_HEIGHT)
		player_data->drawend = SCREEN_HEIGHT - 1;
	if (player_data->side == 0)
		player_data->wall_x = player_data->pos_y
			+ player_data->perp_wall_dist * player_data->raydir_y;
	else
		player_data->wall_x = player_data->pos_x
			+ player_data->perp_wall_dist * player_data->raydir_x;
	player_data->wall_x -= floor(player_data->wall_x);
	player_data->tex_x = (int)(player_data->wall_x * 64.0);
	if (player_data->side == 0 && player_data->raydir_x > 0)
		player_data->tex_x = 64 - player_data->tex_x - 1;
	if (player_data->side == 1 && player_data->raydir_y < 0)
		player_data->tex_x = 64 - player_data->tex_x - 1;
}

void	draw_to_screen(int i, t_data *args, t_player *player_data, t_img *temp)
{
	int	j;

	j = player_data->drawstart;
	if (player_data->drawstart > player_data->drawend)
		player_data->drawstart = 0;
	while (j < player_data->drawend)
	{
		player_data->tex_y = (int) player_data->tex_pos & (64 - 1);
		player_data->tex_pos += player_data->step;
		put_pixel(args->img_data, i, j,
			temp->address[64 * player_data->tex_y + player_data->tex_x]);
		j++;
	}
	drawline(i, player_data->drawstart, player_data->drawend, args);
}

int	domath(void *data)
{
	int		i;
	int		hit;
	t_data	*args;
	t_img	*temp;

	i = 0;
	hit = 0;
	temp = NULL;
	args = (t_data *) data;
	while (i < SCREEN_WIDTH)
	{
		setdata(args->player, i);
		checkside(args->player);
		find_wall(args, args->player, hit);
		temp = select_text(args->player, args);
		func(args->player);
		args->player->step = 1.0 * 64.0 / args->player->lineheight;
		args->player->tex_pos = (args->player->drawstart - SCREEN_HEIGHT
				/ 2 + args->player->lineheight / 2) * args->player->step;
		draw_to_screen(i, args, args->player, temp);
		i++;
	}
	mlx_put_image_to_window(args->mlx,
		args->mlx_win, args->img_data->img, 0, 0);
	return (1);
}
