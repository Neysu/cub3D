/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egatien <egatien@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 04:06:30 by egibeaux          #+#    #+#             */
/*   Updated: 2025/10/28 12:33:26 by egatien          ###   ########.fr       */
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
		return (NULL);
	return (img);
}

int	loadtext(t_data *args)
{
	t_img	**temp;
	int		i;

	i = 0;
	temp = args->wall_text;
	while (temp[i])
	{
		temp[i]->img = opentext(args, temp[i]->path);
		if (!temp[i]->img)
			return (0);
		temp[i]->address = (int *)
			mlx_get_data_addr(temp[i]->img, &temp[i]->bpp,
				&temp[i]->size_line, &temp[i]->endian);
		i++;
	}
	return (1);
}

int	getcolor(int *rgb)
{
	if (!rgb)
		return (0);
	return ((rgb[0] << 16) | (rgb[1] << 8) | rgb[2]);
}
