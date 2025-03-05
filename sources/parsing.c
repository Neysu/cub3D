/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elliot <elliot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 03:02:17 by elliot            #+#    #+#             */
/*   Updated: 2025/03/05 19:34:45 by elliot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include <X11/X.h>
#include <unistd.h>

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

void	findvar(char *line, t_text *text)
{
	if (ft_strnstr(line, "NO", ft_strlen(line)))
		text->north = loadpath(line);
	if (ft_strnstr(line, "SO", ft_strlen(line)))
		text->south = loadpath(line);
	if (ft_strnstr(line, "WE", ft_strlen(line)))
		text->west = loadpath(line);
	if (ft_strnstr(line, "EA", ft_strlen(line)))
		text->east = loadpath(line);
	if (ft_strchr(line, 'C'))
		text->ceiling = loadrgb(line);
	if (ft_strchr(line, 'F'))
	{
		printf("daaaaaaa\n");
		text->floor = loadrgb(line);
	}
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

void	setplayervar(t_data *args)
{
	if (args->player->orientation == 'N')
	{
		args->player->dir_x = 0;
		args->player->dir_y = -1;
		args->player->plane_y = 0;
		args->player->plane_x = FOV * -1;
	}
	if (args->player->orientation == 'S')
	{
		args->player->dir_x = 0;
		args->player->dir_y = 1;
		args->player->plane_y = 0;
		args->player->plane_x = FOV;
	}
	if (args->player->orientation == 'E')
	{
		args->player->dir_x = 1;
		args->player->dir_y = 0;
		args->player->plane_y = FOV * -1;
		args->player->plane_x = 0;
	}
	if (args->player->orientation == 'W')
	{
		args->player->dir_x = -1;
		args->player->dir_y = 0;
		args->player->plane_y = FOV;
		args->player->plane_x = 0;
	}
}

t_data	*open_map(char *file, t_data *args)
{
	char	*line;
	int		fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (NULL);
	args->map = ft_calloc(sizeof(char *), findmaplen(file));
	line = get_next_line(fd);
	while (line != NULL)
	{
		printf("%s", line);
		findvar(line, args->text);
		if (findedges(line))
			args->map = getmap(line, args, fd);
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
	locateplayer(args);
	setplayervar(args);
	return (args);
}
