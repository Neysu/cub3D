/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egatien <egatien@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 19:57:25 by elliot            #+#    #+#             */
/*   Updated: 2025/10/27 13:09:27 by egatien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static t_data	*allocate( void )
{
	t_data	*args;
	int		i;

	i = 0;
	args = ft_calloc(sizeof(t_data), 1);
	args->player = ft_calloc(sizeof(t_player), 1);
	args->text = ft_calloc(sizeof(t_text), 1);
	args->img_data = ft_calloc(sizeof(t_img), 1);
	while (i < 4)
	{
		args->wall_text[i] = ft_calloc(sizeof(t_img), 1);
		args->wall_text[i]->img = NULL;
		args->wall_text[i]->path = NULL;
		i++;
	}
	return (args);
}

static t_data	*loadvar(char **av)
{
	t_data	*args;

	args = allocate();
	if (!get_var(av[1], args))
		return (ft_putendl_fd(ERROR_VAR, STDERR), ft_free(args), NULL);
	if (!get_map(av[1], args))
		return (ft_putendl_fd(ERROR_MAP, STDERR), ft_free(args), NULL);
	args->mlx = mlx_init();
	if (!args->mlx)
		return (ft_putendl_fd(ERROR, 2), ft_free(args), NULL);
	args->mlx_win = mlx_new_window(args->mlx,
			SCREEN_WIDTH, SCREEN_HEIGHT, "CUB3D");
	if (!args->mlx_win)
		return (ft_putendl_fd(ERROR, 2), ft_free(args), NULL);
	args->text->ceiling_color = getcolor(args->text->ceiling);
	args->text->floor_color = getcolor(args->text->floor);
	return (loadtext(args), args);
}

int	main(int ac, char **av)
{
	t_data	*args;

	if (ac != 2)
		return (ft_putendl_fd(ERROR, STDERR_FILENO), 1);
	if (!ft_strnext(av[1], ".cub", ft_strlen(av[1])))
		return (ft_putendl_fd("Wrong file extension", STDERR_FILENO), 1);
	args = loadvar(av);
	if (!args)
		return (1);
	args->img_data->img = mlx_new_image(args->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	args->img_data->address = (int *)
		mlx_get_data_addr(args->img_data->img, &args->img_data->bpp,
			&args->img_data->size_line, &args->img_data->endian);
	mlx_loop_hook(args->mlx, domath, args);
	mlx_hook(args->mlx_win, KeyPress, 1, handle_input_real, args);
	mlx_loop(args->mlx);
	return (0);
}
