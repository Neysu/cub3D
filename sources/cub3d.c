/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egibeaux <egibeaux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 19:57:25 by elliot            #+#    #+#             */
/*   Updated: 2025/03/06 01:55:42 by egibeaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include <X11/X.h>
#include <stdio.h>
#include <string.h>

int	close_window(void *data)
{
	t_data	*args;

	args = (t_data *)data;
	ft_putendl_fd("Bye :)", 1);
	mlx_destroy_window(args->mlx, args->mlx_win);
	args->mlx_win = NULL;
	mlx_destroy_image(args->mlx, args->img_data->img);
	mlx_loop_end(args->mlx);
	exit(0);
}

void	turn(t_player *player_data, double rotSpeed)
{
	double oldDirX;
	double oldPlaneX;

	oldDirX = player_data->dir_x;
	player_data->dir_x = player_data->dir_x * cos(rotSpeed) - player_data->dir_y * sin(rotSpeed);
	player_data->dir_y = oldDirX * sin(rotSpeed) + player_data->dir_y * cos(rotSpeed);
	oldPlaneX = player_data->plane_x;
	player_data->plane_x = player_data->plane_x * cos(rotSpeed) - player_data->plane_y * sin(rotSpeed);
	player_data->plane_y = oldPlaneX * sin(rotSpeed) + player_data->plane_y * cos(rotSpeed);
}

void	move(char **map, t_player *player_data, double movSpeed)
{
	int		y;
	int		x;

	y = (int) player_data->pos_y + player_data->dir_y * movSpeed + 1;
	x = (int) player_data->pos_x + player_data->dir_x * movSpeed + 1;
	printf("%c\n", map[y][x]);
	if (map[y][x] == '1')
		return ;
	player_data->pos_x += player_data->dir_x * movSpeed;
	player_data->pos_y += player_data->dir_y * movSpeed;
}

void	straf(char **map, t_player *player_data, double movSpeed)
{
	(void)map;
	player_data->pos_x += player_data->dir_y * movSpeed;
	player_data->pos_y -= player_data->dir_x * movSpeed;
}

int	handle_input(int keysym, t_data *args)
{
	if (keysym == KEY_ESC)
		close_window(args);
	mlx_clear_window(args->mlx, args->mlx_win);
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
	domath(args, args->player);
	mlx_put_image_to_window(args->mlx, args->mlx_win, args->img_data->img, 0, 0);
	return (0);
}

t_data *loadvar(char **av)
{
	t_data *args;

	args = ft_calloc(sizeof(t_data), 1);
	args->player = ft_calloc(sizeof(t_player), 1);
	args->text = ft_calloc(sizeof(t_text), 1);
	args->img_data = ft_calloc(sizeof(t_img), 1);
	get_var(av[1], args);
	get_map(av[1], args);
	args->mlx = mlx_init();
	if (!args->mlx)
		return (ft_putendl_fd(ERROR, 2), ft_free(args), NULL);
	args->mlx_win = mlx_new_window(args->mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "CUB3D");
	if (!args->mlx_win)
		return (ft_putendl_fd(ERROR, 2), ft_free(args), NULL);
	args->text->ceiling_color = getcolor(args->text->ceiling);
	args->text->floor_color = getcolor(args->text->floor);
	return (args);
}

int	main(int ac, char **av)
{
	t_data	*args;

	if (ac != 2)
		return (ft_putendl_fd(ERROR, 2), 1);
	args = loadvar(av);
	
	args->img_data->img = mlx_new_image(args->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	args->img_data->address = (int *) mlx_get_data_addr(args->img_data->img, &args->img_data->bpp, &args->img_data->size_line, &args->img_data->endian);
	domath(args, args->player);
	mlx_put_image_to_window(args->mlx, args->mlx_win, args->img_data->img, 0, 0);
	mlx_hook(args->mlx_win, KeyPress, 1, &handle_input, args);
	mlx_loop(args->mlx);
	ft_free(args);
	return (0);
}
