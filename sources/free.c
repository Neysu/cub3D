/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egibeaux <egibeaux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 19:55:49 by elliot            #+#    #+#             */
/*   Updated: 2025/03/05 22:41:11 by egibeaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	ft_free_map(char **arr, int len)
{
	int	i;

	if (!arr || !*arr)
		return ;
	i = 0;
	while (i < len)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

static void	ft_free_img(t_data	*args)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (args->wall_text[i]->img)
			mlx_destroy_image(args->mlx, args->wall_text[i]->img);
		if (args->wall_text[i]->path)
			free(args->wall_text[i]->path);
		if (args->wall_text[i])
			free(args->wall_text[i]);
		i++;
	}
}

void	ft_free(t_data *args)
{
	ft_free_map(args->map, args->maplen);
	ft_free_img(args);
	if (args->text) {
		free(args->text->ceiling);
		free(args->text->floor);
		free(args->text->north);
		free(args->text->south);
		free(args->text->west);
		free(args->text->east);
		free(args->text);
	}
	free(args->img_data);
	free(args->player);
	free(args);
}
