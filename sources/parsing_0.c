/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_0.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egatien <egatien@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 03:02:17 by elliot            #+#    #+#             */
/*   Updated: 2025/07/28 09:06:33 by egatien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

char	**getmap(char *line, t_data *args, int fd)
{
	int		i;
	char	*line2;

	i = 0;
	line2 = ft_strdup(line);
	while (ismap(line2) && line2)
	{
		args->map[i] = ft_strdup(line2);
		free(line2);
		line2 = get_next_line(fd);
		i++;
	}
	free(line2);
	args->map[i++] = NULL;
	return (args->map);
}

void	findvar(char *line, t_text *text, t_data *args)
{
	if (ft_strnstr(line, "NO", ft_strlen(line)))
		args->wall_text[0]->path = loadpath(line);
	else if (ft_strnstr(line, "SO", ft_strlen(line)))
		args->wall_text[1]->path = loadpath(line);
	else if (ft_strnstr(line, "WE", ft_strlen(line)))
		args->wall_text[2]->path = loadpath(line);
	else if (ft_strnstr(line, "EA", ft_strlen(line)))
		args->wall_text[3]->path = loadpath(line);
	else if (ft_strchr(line, 'C'))
		text->ceiling = loadrgb(line);
	else if (ft_strchr(line, 'F'))
		text->floor = loadrgb(line);
}

void	locateplayer(t_data *args)
{
	int		y;
	int		x;
	char	**map;

	y = 0;
	map = args->map;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (isplayer(map[y][x]))
			{
				args->player->pos_x = (double) x;
				args->player->pos_y = (double) y;
				args->player->orientation = map[y][x];
				return ;
			}
			x++;
		}
		y++;
	}
}
