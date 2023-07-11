/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 12:39:05 by oaboulgh          #+#    #+#             */
/*   Updated: 2023/07/11 21:11:29 by oaboulgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_square(t_cub *info, int i, int j, int color)
{
	int	a;
	int	b;

	b = i;
	a = j;
	while (i < (b + G_SIZE - 1))
	{
		j = a;
		while (j < (a + G_SIZE - 1))
		{
			my_mlx_pixel_put(info, i, j, color);
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(info->mlx, info->mlx_win, info->img, 0, 0);
}

void	draw_player(t_cub *info, t_palyer *player)
{
	int		a;
	int		b;
	double	movestep;

	player->rotation_angle += player->turn_d * player->rotation_speed;
	movestep = player->walk_d * player->move_speed;
	player->x += cos(player->rotation_angle) * movestep;
	player->y += sin(player->rotation_angle) * movestep;
	draw_circle(info, player);
}

void	draw_circle(t_cub *info, t_palyer *player)
{
	int	a;
	int	b;
	int	n;

	n = (2 * player->radius) + 1;
	a = player->x;
	b = player->y;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			a = i - player->radius;
			b = j - player->radius;
			if ((a * a) + (b * b) <= player->radius * player->radius + 1)
				my_mlx_pixel_put(info, a + (player->x + G_SIZE / 2), \
					b + (player->y + G_SIZE / 2), 0xcc6600);
		}
	}
	mlx_put_image_to_window(info->mlx, info->mlx_win, info->img, 0, 0);
}

void	draw_map(t_cub *info, char **map)
{
	int	i;
	int	j;
	int	a;
	int	b;

	i = 0;
	a = 0;
	while (i < ROW)
	{
		j = 0;
		b = 0;
		while (j < COL)
		{
			if (map[i][j] == '1')
				draw_square(info, j * G_SIZE, i * G_SIZE, 0xFFFFFF);
			else
				draw_square(info, j * G_SIZE, i * G_SIZE, 0xccf2ff);
			j++;
			b += G_SIZE;
		}
		a += 32;
		i++;
	}
}

int	has_a_wall(char **map, int x, int y)
{
	int	i;
	int	j;

	i = G_SIZE;
	j = G_SIZE;
	while (i < COL * G_SIZE)
	{
		j = G_SIZE;
		while (j < ROW * G_SIZE)
		{
			if (y == j && x == i && map[i / G_SIZE][j / G_SIZE] == '0')
			{
				printf("%d\n", i );
				printf("%d\n", j );
				return (1);
			}
			j += G_SIZE;
		}
		i += G_SIZE;
	}
	return (0);
}

int	close_win(void *param)
{
	t_cub	*info;

	info = (t_cub *)param;
	mlx_destroy_window(info->mlx, info->mlx_win);
	exit (0);
	return (0);
}

int	moves(int code, void *param)
{
	t_cub	*info;

	info = (t_cub *)param;
	if (code == 53)
	{
		mlx_destroy_window(info->mlx, info->mlx_win);
		exit (0);
	}
	if (code == 126)
		info->player->walk_d += 1;
	if (code == 125)
		info->player->walk_d -= 1;
	mlx_clear_window(info->mlx, info->mlx_win);
	mlx_destroy_image(info->mlx, info->img);
	info->img = mlx_new_image(info->mlx, COL * G_SIZE, ROW * G_SIZE);
	info->addr = mlx_get_data_addr(info->img, &info->bits_per_pixel, \
		&info->line_length, &info->endian);
	draw_map(info, info->player->map);
	draw_player(info, info->player);
	return (0);
}

void	my_mlx_pixel_put(t_cub *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	main(int ac, char **av)
{
	t_cub		info;
	t_palyer	player;
	char *map[] = {
        // "11111111111",
        // "10000000111",
        // "10011100001",
        // "10000000111",
        // "10000000011",
        // "11000001011",
        // "11100001011",
        // "11111111111",
        "111111111111111",
        "100000000000101",
        "100101000000101",
        "111110000010101",
        "100000000010101",
        "100000001111101",
        "100000000000001",
        "1000000N0000001",
        "111111010111101",
        "100000010000001",
        "111111111111111"
	};

	info.player = &player;
	init_player(&player, map);
	info.mlx = mlx_init();
	info.mlx_win = mlx_new_window(info.mlx, COL * G_SIZE, \
		ROW * G_SIZE, "Cub3D");
	info.img = mlx_new_image(info.mlx, COL * G_SIZE, ROW * G_SIZE);
	info.addr = mlx_get_data_addr(info.img, &info.bits_per_pixel, \
		&info.line_length, &info.endian);
	draw_map(&info, map);
	draw_player(&info, &player);
	mlx_hook(info.mlx_win, 2, 0, moves, &info);
	mlx_hook(info.mlx_win, 17, 0, close_win, &info);
	mlx_loop(info.mlx);
	return (0);
}
