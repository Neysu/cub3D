/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egatien <egatien@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 09:01:37 by egatien           #+#    #+#             */
/*   Updated: 2025/07/28 09:11:53 by egatien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	setplayervar_north_south(t_data *args)
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
}

void	setplayervar_west_east(t_data *args)
{
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

void	setplayervar(t_data *args)
{
	setplayervar_north_south(args);
	setplayervar_west_east(args);
}

t_data	*get_var(char *file, t_data *args)
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
		findvar(line, args->text, args);
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
	locateplayer(args);
	setplayervar(args);
	return (args);
}

t_data	*get_map(char *file, t_data *args)
{
	char	*line;
	int		fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (NULL);
	line = get_next_line(fd);
	while (line != NULL)
	{
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
