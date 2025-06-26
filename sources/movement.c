#include "../cub3d.h"

int	close_window(void *data)
{
	t_data	*args;

	args = (t_data *)data;
	ft_putendl_fd("Bye :)", 1);
	mlx_destroy_window(args->mlx, args->mlx_win);
	args->mlx_win = NULL;
	mlx_destroy_image(args->mlx, args->img_data->img);
	mlx_loop_end(args->mlx);
	exit(0);
}

void	turn(t_player *player_data, double rotSpeed)
{
	double oldDirX;
	double oldPlaneX;

	oldDirX = player_data->dir_x;
	player_data->dir_x = player_data->dir_x * cos(rotSpeed) - player_data->dir_y * sin(rotSpeed);
	player_data->dir_y = oldDirX * sin(rotSpeed) + player_data->dir_y * cos(rotSpeed);
	oldPlaneX = player_data->plane_x;
	player_data->plane_x = player_data->plane_x * cos(rotSpeed) - player_data->plane_y * sin(rotSpeed);
	player_data->plane_y = oldPlaneX * sin(rotSpeed) + player_data->plane_y * cos(rotSpeed);
}

void	move(char **map, t_player *player_data, double movSpeed)
{
    int y;
    int x;

	x = (int) (player_data->pos_x + player_data->dir_x * movSpeed);
	y = (int) (player_data->pos_y + player_data->dir_y * movSpeed);
    if (map[(int)player_data->pos_y][x] != '1')
	     player_data->pos_x += player_data->dir_x * movSpeed;
    if (map[y][(int)player_data->pos_x] != '1')
	     player_data->pos_y += player_data->dir_y * movSpeed;
}

void	straf(char **map, t_player *player_data, double movSpeed)
{
	int x;
	int y;

	x = (int) (player_data->pos_x + player_data->dir_y * movSpeed);
	y = (int) (player_data->pos_y - player_data->dir_x * movSpeed);

    if (map[(int)player_data->pos_y][x] != '1')
		player_data->pos_x += player_data->dir_y * movSpeed;
    if (map[y][(int)player_data->pos_x] != '1')
		player_data->pos_y -= player_data->dir_x * movSpeed;
}
