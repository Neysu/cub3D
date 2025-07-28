/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egatien <egatien@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 23:04:35 by egibeaux          #+#    #+#             */
/*   Updated: 2025/07/28 08:59:54 by egatien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	put_pixel(t_img *data, int x, int y, int color)
{
	int	pixel;

	pixel = y * (data->size_line / 4) + x;
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

void	domath(t_data *args, t_player *player_data)
{
	int		i;
	int		j;
	int		map_x;
	int		map_y;
	int		tex_x;
	int		tex_y;
	int		hit;
	int		side;
	int		lineheight;
	int		drawstart;
	int		drawend;
	double	perp_wall_dist;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	tex_pos;
	double	step;
	double	wall_x;

	t_img	*temp;

	i = 0;
	temp = NULL;
	while (i < SCREEN_WIDTH)
	{
		player_data->camera_x = 2 * i / (double) SCREEN_WIDTH - 1;
		player_data->raydir_x = player_data->dir_x + player_data->plane_x * player_data->camera_x;
		player_data->raydir_y = player_data->dir_y + player_data->plane_y * player_data->camera_x;

		if (player_data->raydir_x == 0)
			delta_dist_x = 1e30;
		else
		 	delta_dist_x = fabs(1 / player_data->raydir_x);
		if (player_data->raydir_y == 0)
			delta_dist_y = 1e30;
		else
			delta_dist_y =  fabs(1 / player_data->raydir_y);

		map_x = (int) player_data->pos_x;
		map_y = (int) player_data->pos_y;

		if (player_data->raydir_x < 0)
		{
			player_data->step_x = -1;
			side_dist_x = (player_data->pos_x - map_x) * delta_dist_x;
		}
		else
		{
			player_data->step_x = 1;
			side_dist_x = (map_x + 1.0 - player_data->pos_x) * delta_dist_x;
		}
		if (player_data->raydir_y < 0)
		{
			player_data->step_y = -1;
			side_dist_y = (player_data->pos_y - map_y) * delta_dist_y;
		}
		else
		{
			player_data->step_y = 1;
			side_dist_y = (map_y + 1.0 - player_data->pos_y) * delta_dist_y;
		}

		hit = 0;

		while (args->map[map_y] && args->map[map_y][map_x] && hit == 0)
		{
			if (side_dist_x < side_dist_y)
			{
				side_dist_x += delta_dist_x;
				map_x += player_data->step_x;
				side = 0;
			}
			else
			{
				side_dist_y += delta_dist_y;
				map_y += player_data->step_y;
				side = 1;
			}
			if (args->map[map_y][map_x] == '1')
				hit = 1;
		}

		if (side == 0)
			perp_wall_dist = (side_dist_x - delta_dist_x);
		else
			perp_wall_dist = (side_dist_y - delta_dist_y);

		lineheight = (int)(SCREEN_HEIGHT / perp_wall_dist);
		drawstart = (lineheight * -1) / 2 + SCREEN_HEIGHT / 2;

		if (side == 0) // Vertical wall: East or West
		{
			if (player_data->raydir_x > 0)
				temp = args->wall_text[2]; // East
			else
				temp = args->wall_text[3]; // West
		}
		else // Horizontal wall: North or South
		{
			if (player_data->raydir_y > 0)
				temp = args->wall_text[1]; // South
			else
				temp = args->wall_text[0]; // North
		}

		if (drawstart < 0)
			drawstart = 0;
		drawend = lineheight / 2 + SCREEN_HEIGHT / 2;

		if (drawend >= SCREEN_HEIGHT)
			drawend = SCREEN_HEIGHT - 1;

		if (side == 0)
			wall_x = player_data->pos_y + perp_wall_dist * player_data->raydir_y;
		else
			wall_x = player_data->pos_x + perp_wall_dist * player_data->raydir_x;
		wall_x -= floor(wall_x);

		tex_x = (int) (wall_x * 64.0);

		if (side == 0 && player_data->raydir_x > 0)
			tex_x = 64 - tex_x - 1;
		if (side == 1 && player_data->raydir_y < 0)
			tex_x = 64 - tex_x - 1;

		step = 1.0 * 64.0 / lineheight;

		tex_pos = (drawstart - SCREEN_HEIGHT / 2 + lineheight / 2) * step;
		j = drawstart;
		while (j < drawend)
		{
			tex_y = (int) tex_pos & (64 - 1);
			tex_pos += step;
			put_pixel(args->img_data, i, j, temp->address[64 * tex_y + tex_x]);
			j++;
		}

		drawline(i, drawstart, drawend, args);
		i++;
	}
}
