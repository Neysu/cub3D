/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egatien <egatien@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 19:57:25 by elliot            #+#    #+#             */
/*   Updated: 2025/07/28 08:54:36 by egatien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include <malloc.h>

int handle_input_real(int keysym, void *param)
{
	t_data	*args;

	args = (t_data *) param;
	if (keysym == KEY_ESC)
		close_window(args);
	//mlx_clear_window(args->mlx, args->mlx_win);
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
	//domath(args, args->player);
	//mlx_put_image_to_window(args->mlx,
	//	args->mlx_win, args->img_data->img, 0, 0);
	return (0);
}

void	loadtext(t_data *args)
{
	t_img	**temp;
	int		i;

	i = 0;
	temp = args->wall_text;
	while (temp[i])
	{
		temp[i]->img = opentext(args, temp[i]->path);
		temp[i]->address = (int *)
			mlx_get_data_addr(temp[i]->img, &temp[i]->bpp,
				&temp[i]->size_line, &temp[i]->endian);
		i++;
	}
}

t_data	*loadvar(char **av)
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
		i++;
	}
	get_var(av[1], args);
	get_map(av[1], args);
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
	args->img_data->img = mlx_new_image(args->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	args->img_data->address = (int *)
		mlx_get_data_addr(args->img_data->img, &args->img_data->bpp,
			&args->img_data->size_line, &args->img_data->endian);
	mlx_loop_hook(args->mlx, domath, args);
	mlx_hook(args->mlx_win, KeyPress, 1, handle_input_real, args);
	mlx_loop(args->mlx);
	return (0);
}
