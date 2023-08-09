/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 12:39:05 by oaboulgh          #+#    #+#             */
/*   Updated: 2023/08/09 20:11:29 by oaboulgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_square(t_cub *info, int i, int j, int color)
{
	int	a;
	int	b;

	b = i;
	a = j;
	while (i < (b + G_SIZE * MINI_MAP_SCALE))
	{
		j = a;
		while (j < (a + G_SIZE * MINI_MAP_SCALE))
		{
			if (i >= 0 && j >= 0 && i <= 200 && j <= 200)
				my_mlx_pixel_put(&info->img, i, j, color);
			j++;
		}
		i++;
	}
}

void	draw_map(t_cub *info, char **map)
{
	int	i;
	int	j;
	int	a;
	int	b;

	i = 0;
	b = 100 - info->player->y * MINI_MAP_SCALE;
	while (map[i])
	{
		j = 0;
		a = 100 - info->player->x * MINI_MAP_SCALE;
		while (map[i][j])
		{
			if (map[i][j] == '1')
				draw_square(info, a, b, 0xFFFFFF);
			else if (map[i][j] == ' ')
				draw_square(info, a, b, 0x000000);
			else
				draw_square(info, a, b, 0xccf2ff);
			a += G_SIZE * MINI_MAP_SCALE;
			j++;
		}
		b += G_SIZE * MINI_MAP_SCALE;
		i++;
	}
}

int	close_win(void *param)
{
	t_cub	*info;

	info = (t_cub *)param;
	mlx_destroy_window(info->mlx, info->mlx_win);
	exit (0);
	return (0);
}


void	my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_len + x * (data->bpp / 8));
	*(unsigned int *)dst = color;
}

int	get_sign(float nbr)
{
	if (nbr >= 0)
		return (1);
	return (-1);
}

int handle_keypress(int keycode, void *param)
{
	t_cub *info;
	
	info = (t_cub *)param;
	if (keycode == 53)
	{
		mlx_destroy_window(info->mlx, info->mlx_win);
		exit (0);
	}
	if (keycode == 12)
		info->player->move_forward_l = 1;
	if (keycode == 14)
		info->player->move_forward_r = 1;
	if (keycode == 49 && !info->player->stop)
		info->player->shot = 1;
	if (keycode == 126)
		info->player->move_forward = 1;
	else if (keycode == 125)
		info->player->move_backward = 1;
	else if (keycode == 123)
		info->player->rotate_left = 1;
	else if (keycode == 124)
		info->player->rotate_right = 1;
	return (0);
}

int	handle_keyrelease(int keycode, void *param)
{
	t_cub	*info;
	
	info = (t_cub *)param;
	if (keycode == 12)
		info->player->move_forward_l = 0;
	if (keycode == 14)
		info->player->move_forward_r = 0;
	if (keycode == 49)
	{
		info->player->shot = 0;
		info->player->stop = 0;
	}
	if (keycode == 126)
		info->player->move_forward = 0;
	else if (keycode == 125)
		info->player->move_backward = 0;
	else if (keycode == 123)
		info->player->rotate_left = 0;
	else if (keycode == 124)
		info->player->rotate_right = 0;

	return (0);
}

void	color_background(t_cub *info)
{
	int	i;
	int	j;

	j = 0;
	while (j < info->player->middle_of_screen)
	{
		i = 0;
		while (i < COL * G_SIZE)
		{
			if (i >= 0 && j >= 0 && i < G_SIZE * COL && j < G_SIZE * ROW)
				my_mlx_pixel_put(&info->img, i, j, 0x99d6ff);
			i++;
		}
		j++;
	}
	i = 0;
	j = info->player->middle_of_screen;
	while (j < G_SIZE * ROW)
	{
		i = 0;
		while (i < COL * G_SIZE)
		{
			if (i >= 0 && j >= 0 && i <= G_SIZE * COL && j <= G_SIZE * ROW)
				my_mlx_pixel_put(&info->img, i, j, 0x737373);
			i++;
		}
		j++;
	}
	
}

int	long_line(char **map)
{
	int	i;
	int	j;
	int	x;

	i = 0;
	x = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
			j++;
		if (j > x)
			x = j;
		i++;
	}
	return (x);
}

int	height_of_map(char **map)
{
	int	i;

	i = 0;
	while (map[i])
		i++;
	return (i);
	
}

void draw_sprite(t_cub *info)
{
	int		i;
	int		j;
	float	difx;
	float	dify;
	float	dist;
	float	y;
	float	x;
	float	angle;

	angle = scale_angle(info->player->rotation_angle);
	difx = info->enemy.x - info->player->x;
	dify = info->enemy.y - info->player->y;
	dist = sqrt(difx * difx + dify * dify);

	
	i = 0;
	j = 0;
	y = info->enemy.y;
	x = info->enemy.x;
	while (i < 50)
	{
		j = 0;
		while (j < 50)
		{
			if ((j + x) > 0 && (j + x) < (COL * G_SIZE) && (i + y) > 0 && (i + y) < (ROW * G_SIZE))
				my_mlx_pixel_put(&info->img, j + x, i + y, 0xffffff);
			j++;
		}
		i++;
	}
}


int	main(int ac, char **av)
{
	t_cub		info;
	t_player	player;
	// t_info		*info2;
	// t_cubt		*cub;

	(void)ac;
	(void)av;
	char *map[] = {
		"111111111111111\0",
		"100000000000101\0",
		"100101000000101\0",
		"101110000010101\0",
		"1000000000D0101\0",
        "100000001101101\0",
        "100000001101101\0",
		"100000000000001\0",
		"1000000N0000001\0",
		"111D110001D1101\0",
		"100000000000001\0",
        "111111111111111\0",
		NULL
	};
	// if (ac != 2)
	// {
	// 	printf("Error\n");
	// 	exit(0);
	// }
	// info2 = parcing(av[1], &cub);
	// (void)av;
	// (void)ac;

	info.player = &player;
	init_player(&player, map);
	info.mlx = mlx_init();
	if (info.mlx == NULL)
		return (printf("Error init window\n"), 1);
	info.mlx_win = mlx_new_window(info.mlx, COL * 64, \
		ROW * 64, "Cub3D");
	mlx_hook(info.mlx_win, 17, 0, close_win, &info);
	mlx_hook(info.mlx_win, 2, 0, handle_keypress, &info);
	mlx_hook(info.mlx_win, 3, 0, handle_keyrelease, &info);
	mlx_hook(info.mlx_win, 6, 0, handle_mouse_move, &info);
	mlx_loop_hook(info.mlx, move_and_draw, &info);
	mlx_loop(info.mlx);\
	return (0);
}
