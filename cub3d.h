/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egibeaux <egibeaux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 19:54:12 by elliot            #+#    #+#             */
/*   Updated: 2025/03/04 02:29:02 by egibeaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minilibx/mlx.h"
#include "libft/libft.h"
#include "ft_printf/ft_printf.h"
#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include <X11/keysym.h>
#include <X11/X.h>

#define KEY_ESC 65307
#define KEY_LEAVE 17
#define KEY_W 119
#define KEY_S 115
#define KEY_A 97
#define KEY_D 100
#define KEY_UP 65362
#define KEY_DOWN 65364
#define KEY_RIGHT 65363
#define KEY_LEFT 65361

#define ERROR "Error"

#define SCREEN_HEIGHT 1024
#define SCREEN_WIDHT 1280

typedef struct	s_player
{
	double		posy;
	double		posx;
	double		dirx;
	double		diry;
	double		planex;
	double		planey;
	char		orientation;
}				t_player;

typedef struct s_text
{
	int			*ceiling;
	int			*floor;
	char		*north;
	char		*south;
	char		*east;
	char		*west;
}				t_text;

typedef struct	s_img
{
	void	*img;
	int		*address;
	int		endian;
	int		size_line;
	int		bpp;
}				t_img;

typedef struct	s_data
{
	void		*mlx;
	void		*mlx_win;
	char		**map;
	t_img		*img_data;
	t_text		*text;
	t_player	*player;
}				t_data;

size_t	findmaplen(char *map);

void	ft_free(t_data *args);

int		*loadrgb(char *line);

int		charmap(char c);
int		ismap(char *line);
int		isplayer(char c);
int		findedges(char *line);

char	*loadpath(char *line);

t_data	*open_map(char *map, t_data *args);