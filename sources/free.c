/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elliot <elliot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 19:55:49 by elliot            #+#    #+#             */
/*   Updated: 2025/03/02 19:40:16 by elliot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_free(t_data *args)
{
	ft_free_arr(args->map);
	free(args->ceiling);
	free(args->floor);
	free(args->north);
	free(args->south);
	free(args->west);
	free(args->east);
	free(args);
}
