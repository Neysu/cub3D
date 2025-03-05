/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egibeaux <egibeaux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 19:55:49 by elliot            #+#    #+#             */
/*   Updated: 2025/03/04 22:19:54 by egibeaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_free(t_data *args)
{
	ft_free_arr(args->map);
	free(args->text->ceiling);
	free(args->text->floor);
	free(args->text->north);
	free(args->text->south);
	free(args->text->west);
	free(args->text->east);
	free(args->text);
	free(args->img_data);
	free(args);
}
