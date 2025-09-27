/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egatien <egatien@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 03:21:35 by elliot            #+#    #+#             */
/*   Updated: 2025/07/28 08:42:34 by egatien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	ismap(char *line)
{
	int		i;

	if (!line)
		return (0);
	i = 0;
	while (line[i] && line[i] != '\n')
	{
		if (!charmap(line[i]))
			return (0);
		i++;
	}
	return (1);
}

size_t	findmaplen(char *file)
{
	int		fd;
	char	*line;
	int		i;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (0);
	line = get_next_line(fd);
	i = 0;
	while (line)
	{
		if (ismap(line))
			++i;
		free(line);
		line = get_next_line(fd);
	}
	close (fd);
	return (i);
}

int	findedges(char *line)
{
	int	i;

	i = 0;
	if (line[i] == '\n')
		return (0);
	while (line[i] != '\n')
	{
		if (line[i] != '1' && line[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

char	*loadpath(char *line)
{
	char	**pathtotext;
	char	*path;

	pathtotext = ft_split(line, ' ');
	if (ft_arrlen(pathtotext) != 2)
		return (NULL);
	path = ft_strdup(pathtotext[1]);
	ft_free_arr(pathtotext);
	return (path);
}

int	*loadrgb(char *line)
{
	int		i;
	int		*rgb;
	char	*temp;
	char	**tab;

	tab = ft_split(line, ' ');
	i = 0;
	temp = ft_strdup(tab[1]);
	ft_free_arr(tab);
	tab = ft_split(temp, ',');
	free(temp);
	rgb = ft_calloc(sizeof(int), ft_arrlen(tab) + 1);
	while (tab[i])
	{
		rgb[i] = ft_atoi(tab[i]);
		i++;
	}
	ft_free_arr(tab);
	return (rgb);
}
