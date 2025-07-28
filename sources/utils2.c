/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egatien <egatien@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 04:06:30 by egibeaux          #+#    #+#             */
/*   Updated: 2025/07/28 08:42:38 by egatien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	*opentext(t_data *args, char *path)
{
	void	*img;
	int		width;
	int		height;

	img = NULL;
	img = mlx_xpm_file_to_image(args->mlx, path, &width, &height);
	if (!img)
		return (ft_free(args), NULL);
	return (img);
}

int	getcolor(int *rgb)
{
	if (!rgb)
		return (0);
	return ((rgb[0] << 16) | (rgb[1] << 8) | rgb[2]);
}
