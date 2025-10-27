/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering_0.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egatien <egatien@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 23:04:35 by egibeaux          #+#    #+#             */
/*   Updated: 2025/10/27 13:26:43 by egatien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	put_pixel(t_img *data, int x, int y, int color)
{
	unsigned int	pixel;

	pixel = y * (data->size_line / 4) + x;
	if (pixel > (SCREEN_HEIGHT * SCREEN_WIDTH))
		return ;
	data->address[pixel] = color;
}

void	drawline(int x, int start, int end, t_data *args)
{
	int			i;

	i = 0;
	while (i < start)
	{
		put_pixel(args->img_data, x, i, args->text->ceiling_color);
		i++;
	}
	while (i < end)
		i++;
	while (i < SCREEN_HEIGHT)
	{
		put_pixel(args->img_data, x, i, args->text->floor_color);
		i++;
	}
}

void	checkside(t_player *player_data)
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
		player_data->side_dist_x = (player_data->map_x
				+ 1.0 - player_data->pos_x) * player_data->delta_dist_x;
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
		player_data->side_dist_y = (player_data->map_y
				+ 1.0 - player_data->pos_y) * player_data->delta_dist_y;
	}
}

static void	find_wall_bis(t_player *player_data)
{
	if (player_data->side == 0)
		player_data->perp_wall_dist
			= (player_data->side_dist_x - player_data->delta_dist_x);
	else
		player_data->perp_wall_dist
			= (player_data->side_dist_y - player_data->delta_dist_y);
	player_data->lineheight
		= (unsigned int)(SCREEN_HEIGHT / player_data->perp_wall_dist);
	player_data->drawstart
		= (player_data->lineheight * -1) / 2 + SCREEN_HEIGHT / 2;
}

void	find_wall(t_data *args, t_player *player_data, int hit)
{
	hit = 0;
	while (args->map[player_data->map_y]
		&& args->map[player_data->map_y][player_data->map_x] && !hit)
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
	find_wall_bis(player_data);
}
