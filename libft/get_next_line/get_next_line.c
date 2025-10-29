/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egatien <egatien@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 11:43:14 by egatien           #+#    #+#             */
/*   Updated: 2025/10/29 14:28:45 by egatien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int	readfile(char *buffer, int fd)
{
	int	readcheck;

	readcheck = (int)read(fd, buffer, BUFFER_SIZE);
	if (readcheck > 0)
		buffer[readcheck] = '\0';
	return (readcheck);
}

char	*cutstringwhen_n(char *line)
{
	int	i;

	i = 0;
	while (line[i] != '\n' && line[i] != '\0')
		i++;
	if (line[i] == '\n')
		line[i + 1] = '\0';
	return (line);
}

void	decalebuffer(char *buffer)
{
	int		i;
	char	*newline_ptr;

	i = 0;
	newline_ptr = ft_strchr(buffer, '\n');
	if (newline_ptr)
	{
		newline_ptr++;
		while (newline_ptr[i])
		{
			buffer[i] = newline_ptr[i];
			i++;
		}
		buffer[i] = '\0';
	}
	else
		buffer[0] = '\0';
}

char	*read_until_newline(int fd, char *buffer, int *readcheck)
{
	char	*line;
	char	*temp;

	line = ft_strdup(buffer);
	if (!line)
		return (NULL);
	while (!ft_strchr(line, '\n'))
	{
		*readcheck = readfile(buffer, fd);
		if (*readcheck <= 0)
			break ;
		temp = line;
		line = ft_strjoin(line, buffer);
		free(temp);
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	char		*line;
	int			readcheck;

	if (fd == -1)
		return (NULL);
	readcheck = 0;
	line = read_until_newline(fd, buffer, &readcheck);
	if (readcheck <= 0 && buffer[0] == '\0')
	{
		if (line)
			free(line);
		return (NULL);
	}
	decalebuffer(buffer);
	cutstringwhen_n(line);
	return (line);
}
