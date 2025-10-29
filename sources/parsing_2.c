/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egatien <egatien@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 12:21:26 by egatien           #+#    #+#             */
/*   Updated: 2025/10/29 12:44:50 by egatien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	check_rgb(t_text *text)
{
	int	i;

	i = 0;
	while (text->ceiling[i])
	{
		if (text->ceiling[i] > 255)
			return (0);
		i++;
	}
	i = 0;
	while (text->floor[i])
	{
		if (text->floor[i] > 255)
			return (0);
		i++;
	}
	return (1);
}

int	check_map(char **map)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (map[y])
	{
		if (map[y][0] == '\0')
			return (0);
		while (map[y][x])
		{
			if (map[y][x] != '1' && map[y][x] != '0'
					&& map[y][x] != 'S' && map[y][x] != ' ')
				return (0);
			x++;
		}
		x = 0;
		y++;
	}
	return (1);
}

int	check_parsing(t_data *args)
{
	if (!check_map(args->map))
		return (0);
	if (!check_rgb(args->text))
		return (0);
	return (1);
}