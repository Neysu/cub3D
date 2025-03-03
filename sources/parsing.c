/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elliot <elliot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 03:02:17 by elliot            #+#    #+#             */
/*   Updated: 2025/03/02 20:41:11 by elliot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include <unistd.h>

int	charmap(char c)
{
	if (c == '1' || c == '0' || c == 'N' || c == 'W' || c == 'S' || c == 'E' || c == ' ')
		return (1);
	return (0);
}

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

void	findvar(char *line, t_data *args)
{
	if (ft_strnstr(line, "NO", ft_strlen(line)))
		args->north = loadpath(line);
	else if (ft_strnstr(line, "SO", ft_strlen(line)))
		args->south = loadpath(line);
	else if (ft_strnstr(line, "WE", ft_strlen(line)))
		args->west = loadpath(line);
	else if (ft_strnstr(line, "EA", ft_strlen(line)))
		args->east = loadpath(line);
	else if (ft_strchr(line, 'C'))
		args->ceiling = loadrgb(line);
	else if (ft_strchr(line, 'F'))
		args->floor = loadrgb(line);
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
		findvar(line, args);
		if (findedges(line))
			args->map = getmap(line, args, fd);
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
	return (args);
}
