/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egatien <egatien@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 08:45:52 by egatien           #+#    #+#             */
/*   Updated: 2025/10/27 13:13:26 by egatien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	close_window(void *data)
{
	t_data	*args;

	args = (t_data *)data;
	ft_putendl_fd("Bye :)", 1);
	mlx_destroy_window(args->mlx, args->mlx_win);
	args->mlx_win = NULL;
	mlx_destroy_image(args->mlx, args->img_data->img);
	ft_free(args);
	exit(0);
}

int	handle_input_real(int keysym, void *param)
{
	t_data	*args;

	args = (t_data *) param;
	if (keysym == KEY_ESC)
		close_window(args);
	if (keysym == KEY_W)
		move(args->map, args->player, MOV_SPEED);
	if (keysym == KEY_S)
		move(args->map, args->player, (MOV_SPEED * -1));
	if (keysym == KEY_D)
		straf(args->map, args->player, MOV_SPEED);
	if (keysym == KEY_A)
		straf(args->map, args->player, (MOV_SPEED * -1));
	if (keysym == KEY_RIGHT)
		turn(args->player, (ROT_SPEED * -1));
	if (keysym == KEY_LEFT)
		turn(args->player, ROT_SPEED);
	return (0);
}

void	turn(t_player *player_data, double rotSpeed)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = player_data->dir_x;
	player_data->dir_x = player_data->dir_x
		* cos(rotSpeed) - player_data->dir_y * sin(rotSpeed);
	player_data->dir_y = old_dir_x
		* sin(rotSpeed) + player_data->dir_y * cos(rotSpeed);
	old_plane_x = player_data->plane_x;
	player_data->plane_x = player_data->plane_x
		* cos(rotSpeed) - player_data->plane_y * sin(rotSpeed);
	player_data->plane_y = old_plane_x
		* sin(rotSpeed) + player_data->plane_y * cos(rotSpeed);
}

void	move(char **map, t_player *player_data, double movSpeed)
{
	int	y;
	int	x;

	if (movSpeed > 0)
	{
		x = (int)(player_data->pos_x
				+ player_data->dir_x * (movSpeed + MARGIN));
		y = (int)(player_data->pos_y
				+ player_data->dir_y * (movSpeed + MARGIN));
	}
	if (movSpeed < 0)
	{
		x = (int)(player_data->pos_x
				+ player_data->dir_x * (movSpeed - MARGIN));
		y = (int)(player_data->pos_y
				+ player_data->dir_y * (movSpeed - MARGIN));
	}
	if (map[(int) player_data->pos_y][x] != '1')
		player_data->pos_x += player_data->dir_x * movSpeed;
	else
		return ;
	if (map[y][(int) player_data->pos_x] != '1')
		player_data->pos_y += player_data->dir_y * movSpeed;
}

void	straf(char **map, t_player *player_data, double movSpeed)
{
	int	x;
	int	y;

	if (movSpeed > 0)
	{
		x = (int)(player_data->pos_x
				+ player_data->dir_y * (movSpeed + MARGIN));
		y = (int)(player_data->pos_y
				- player_data->dir_x * (movSpeed + MARGIN));
	}
	else
	{
		x = (int)(player_data->pos_x
				+ player_data->dir_y * (movSpeed - MARGIN));
		y = (int)(player_data->pos_y
				- player_data->dir_x * (movSpeed - MARGIN));
	}
	if (map[(int) player_data->pos_y][x] != '1')
		player_data->pos_x += player_data->dir_y * movSpeed;
	if (map[y][(int) player_data->pos_x] != '1')
		player_data->pos_y -= player_data->dir_x * movSpeed;
}
