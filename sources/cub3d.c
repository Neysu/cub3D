/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elliot <elliot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 19:57:25 by elliot            #+#    #+#             */
/*   Updated: 2025/03/03 08:38:51 by elliot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include <X11/X.h>

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
		ft_printf("you pressed W\n");
	return (0);
}

int	main(int ac, char **av)
{
	t_data	*args;

	if (ac != 2)
		return (ft_putendl_fd(ERROR, 2), 1);
	args = ft_calloc(sizeof(t_data), 1);
	args->player = ft_calloc(sizeof(t_player), 1);
	open_map(av[1], args);
	args->mlx = mlx_init();
	if (!args->mlx)
		return (ft_putendl_fd(ERROR, 2), ft_free(args), 1);
	args->mlx_win = mlx_new_window(args->mlx, 800, 600, "CUB3D");
	mlx_hook(args->mlx_win, KeyPress, 1, &handle_input, args);
	mlx_loop(args->mlx);
	ft_free(args);
	return (0);
}
