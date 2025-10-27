/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floodfill.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egatien <egatien@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 15:08:41 by egatien           #+#    #+#             */
/*   Updated: 2025/10/27 11:56:02 by egatien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

char	*search_start(char **mat, int *x, int *y)
{
	int	i;
	int	j;

	i = 0;
	while (mat[i])
	{
		j = 0;
		while (mat[i][j] != '\0')
		{
			if (isplayer(mat[i][j]))
			{
				*x = j;
				*y = i;
				return (&mat[i][j]);
			}
			j++;
		}
		i++;
	}
	return (NULL);
}

int	start_floodfill(int x, int y, char **mat)
{
	if (x < 0 || y < 0 || mat[y] == NULL || mat[y][x] == '\0')
		return (0);
	if (mat[y][x] != '0')
		return (1);
	mat[y][x] = 'V';
	if (!start_floodfill(x, y - 1, mat))
		return (0);
	if (!start_floodfill(x, y + 1, mat))
		return (0);
	if (!start_floodfill(x - 1, y, mat))
		return (0);
	if (!start_floodfill(x + 1, y, mat))
		return (0);
	return (1);
}

char	**create_mat(char **mat)
{
	char	**result;
	int		i;
	int		count;

	count = 0;
	i = 0;
	while (mat[count] != NULL)
		count++;
	result = malloc(sizeof(char *) * (count + 1));
	if (!result)
		return (NULL);
	while (mat[i] != NULL)
	{
		result[i] = ft_strdup(mat[i]);
		i++;
	}
	result[i] = NULL;
	return (result);
}

int	floodfill(char **mat)
{
	char	*start;
	int		x;
	int		y;
	char	**newmat;
	int		result;

	newmat = create_mat(mat);
	if (!newmat)
		return (0);
	start = search_start(newmat, &x, &y);
	if (!start)
	{
		ft_free_arr(newmat);
		return (0);
	}
	(*start) = '0';
	result = start_floodfill(x, y, newmat);
	ft_free_arr(newmat);
	return (result);
}
