/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egibeaux <egibeaux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 23:04:35 by egibeaux          #+#    #+#             */
/*   Updated: 2025/03/06 00:42:43 by egibeaux         ###   ########.fr       */
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
	int		texX;
	int		texY;
	int		hit;
	int		side;
	int		lineheight;
	int		drawstart;
	int		drawend;
	double	perpWallDist;
	double	sideDistX;
	double	sideDistY;
	double	deltaDistX;
	double	deltaDistY;
	double	texPos;
	double	step;
	double	wallX;

	t_img	*temp;

	i = 0;
	temp = NULL;
	while (i < SCREEN_WIDTH)
	{
		player_data->camera_x = 2 * i / (double) SCREEN_WIDTH - 1;
		player_data->raydir_x = player_data->dir_x + player_data->plane_x * player_data->camera_x;
		player_data->raydir_y = player_data->dir_y + player_data->plane_y * player_data->camera_x;

		if (player_data->raydir_x == 0)
			deltaDistX = 1e30;
		else
		 	deltaDistX = fabs(1 / player_data->raydir_x);
		if (player_data->raydir_y == 0)
			deltaDistY = 1e30;
		else
			deltaDistY =  fabs(1 / player_data->raydir_y);

		map_x = (int) player_data->pos_x;
		map_y = (int) player_data->pos_y;

		if (player_data->raydir_x < 0)
		{
			player_data->step_x = -1;
			sideDistX = (player_data->pos_x - map_x) * deltaDistX;
		}
		else
		{
			player_data->step_x = 1;
			sideDistX = (map_x + 1.0 - player_data->pos_x) * deltaDistX;
		}
		if (player_data->raydir_y < 0)
		{
			player_data->step_y = -1;
			sideDistY = (player_data->pos_y - map_y) * deltaDistY;
		}
		else
		{
			player_data->step_y = 1;
			sideDistY = (map_y + 1.0 - player_data->pos_y) * deltaDistY;
		}

		hit = 0;

		while (args->map[map_y] && args->map[map_y][map_x] && hit == 0)
		{
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				map_x += player_data->step_x;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				map_y += player_data->step_y;
				side = 1;
			}
			if (args->map[map_y][map_x] == '1')
				hit = 1;
		}

		if (side == 0)
			perpWallDist = (sideDistX - deltaDistX);
		else
			perpWallDist = (sideDistY - deltaDistY);

		lineheight = (int)(SCREEN_HEIGHT / perpWallDist);
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
			wallX = player_data->pos_y + perpWallDist * player_data->raydir_y;
		else
			wallX = player_data->pos_x + perpWallDist * player_data->raydir_x;
		wallX -= floor(wallX);

		texX = (int) (wallX * 64.0);

		if (side == 0 && player_data->raydir_x > 0)
			texX = 64 - texX - 1;
		if (side == 1 && player_data->raydir_y < 0)
			texX = 64 - texX - 1;

		step = 1.0 * 64.0 / lineheight;

		texPos = (drawstart - SCREEN_HEIGHT / 2 + lineheight / 2) * step;
		j = drawstart;
		while (j < drawend)
		{
			texY = (int) texPos & (64 - 1);
			texPos += step;
			put_pixel(args->img_data, i, j, temp->address[64 * texY + texX]);
			j++;
		}

		drawline(i, drawstart, drawend, args);
		i++;
	}
}
