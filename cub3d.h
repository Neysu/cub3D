/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egatien <egatien@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 19:54:12 by elliot            #+#    #+#             */
/*   Updated: 2025/07/28 09:06:07 by egatien          ###   ########.fr       */
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
#define NORTH_WALL "textures/mossy.xpm"
#define WEST_WALL "textures/bluestone.xpm"
#define SOUTH_WALL "textures/redbrick.xpm"
#define EAST_WALL "textures/mossy.xpm"
#define SCREEN_HEIGHT 600
#define SCREEN_WIDTH 800
#define FOV	0.66
#define ROT_SPEED 0.1
#define MOV_SPEED 0.1

typedef struct	s_player
{
	int			map_x;
	int			map_y;
	double		pos_y;
	double		pos_x;
	double		dir_x;
	double		dir_y;
	double		raydir_x;
	double		raydir_y;
	double		deltadist_x;
	double		deltadist_y;
	double		camera_x;
	double		plane_x;
	double		plane_y;
	double		step_x;
	double		step_y;
	char		orientation;
}				t_player;

typedef struct s_text
{
	int			*ceiling;
	int			*floor;
	int			ceiling_color;
	int			floor_color;
	char		*north;
	char		*south;
	char		*east;
	char		*west;
}				t_text;

typedef struct	s_img
{
	void			*img;
	char			*path;
	int				*address;
	int				endian;
	int				size_line;
	int				bpp;
}				t_img;

typedef struct	s_data
{
	void		*mlx;
	void		*mlx_win;
	char		**map;
	t_img		*img_data;
	t_img		*wall_text[5];
	t_text		*text;
	t_player	*player;
}				t_data;

size_t	findmaplen(char *map);

void	*opentext(t_data *args, char *path);

void	ft_free(t_data *args);
void	domath(t_data *args, t_player *player_data);
void	turn(t_player *player_data, double rotSpeed);
void	put_pixel(t_img *data, int x, int y, int color);
void	move(char **map, t_player *player_data, double movSpeed);
void	straf(char **map, t_player *player_data, double movSpeed);
void	drawline(int i, int start, int end, t_data *args);

int		*loadrgb(char *line);

int		charmap(char c);
int		isplayer(char c);
int		ismap(char *line);
int		getcolor(int *rgb);
int		findedges(char *line);
int		close_window(void *data);

char	*loadpath(char *line);

t_data	*get_var(char *map, t_data *args);
t_data	*get_map(char *file, t_data *args);

void	findvar(char *line, t_text *text, t_data *args);
void	locateplayer(t_data *args);
char	**getmap(char *line, t_data *args, int fd);