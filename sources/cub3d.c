/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egibeaux <egibeaux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 19:57:25 by elliot            #+#    #+#             */
/*   Updated: 2025/03/05 03:54:08 by egibeaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include <X11/X.h>
#include <string.h>

int	close_window(void *data)
{
	t_data	*args;

	args = (t_data *)data;
	ft_putendl_fd("Bye :)", 1);
	mlx_destroy_window(args->mlx, args->mlx_win);
	args->mlx_win = NULL;
	mlx_loop_end(args->mlx);
	return (0);
}

int	handle_input(int keysym, t_data *args)
{
	if (keysym == KEY_ESC)
		close_window(args);
	if (keysym == KEY_W)
		ft_printf("pressed W\n");
	return (0);
}

t_data *loadvar(char **av)
{
	t_data *args;

	args = ft_calloc(sizeof(t_data), 1);
	args->player = ft_calloc(sizeof(t_player), 1);
	args->text = ft_calloc(sizeof(t_text), 1);
	args->img_data = ft_calloc(sizeof(t_img), 1);
	open_map(av[1], args);
	args->mlx = mlx_init();
	if (!args->mlx)
		return (ft_putendl_fd(ERROR, 2), ft_free(args), NULL);
	args->mlx_win = mlx_new_window(args->mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "CUB3D");
	if (!args->mlx_win)
		return (ft_putendl_fd(ERROR, 2), ft_free(args), NULL);
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
