/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 12:39:05 by oaboulgh          #+#    #+#             */
/*   Updated: 2023/07/17 01:48:06 by oaboulgh         ###   ########.fr       */
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

int	close_win(void *param)
{
	t_cub	*info;

	info = (t_cub *)param;
	mlx_destroy_window(info->mlx, info->mlx_win);
	exit (0);
	return (0);
}

int	has_wall(float x, float y, t_cub *info)
{
	int	i, j;
	
	j = x / G_SIZE;
	i = y / G_SIZE;
	// x = floor(x / G_SIZE);
	// y = floor(y / G_SIZE);
	if (info->player->map[i][j] == '1')
		return (1);
	return (0);
}

void	my_mlx_pixel_put(t_cub *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void move_object(t_player *player, t_cub *info)
{
	float	x;
	float	y;

	x = player->x;
	y = player->y;
    if (player->move_forward)
    {
        player->x += MOVE_SPEED * cos(player->rotation_angle);
        player->y += MOVE_SPEED * sin(player->rotation_angle);
		if (has_wall(x, player->y, info))
			player->y = y;
		if (has_wall(player->x, y, info))
			player->x = x;
    }
    if (player->move_backward)
    {
        player->x -= MOVE_SPEED * cos(player->rotation_angle);
        player->y -= MOVE_SPEED * sin(player->rotation_angle);
		if (has_wall(x, player->y, info))
			player->y = y;
		if (has_wall(player->x, y, info))
			player->x = x;
    }
    if (player->rotate_left)
    {
        player->rotation_angle -= player->rotation_speed;
    }
    if (player->rotate_right)
    {
        player->rotation_angle += player->rotation_speed;
    }
}

int handle_keypress(int keycode, void *param)
{
	t_cub *info;
	
	info = (t_cub *)param;
	// Key Press
	if (keycode == 126) // 'W' key
		info->player->move_forward = 1;
	else if (keycode == 125) // 'S' key
		info->player->move_backward = 1;
	else if (keycode == 123) // 'A' key
		info->player->rotate_left = 1;
	else if (keycode == 124) // 'D' key
		info->player->rotate_right = 1;
	return (0);
}

int	handle_keyrelease(int keycode, void *param)
{
	t_cub	*info;
	
	info = (t_cub *)param;
	// Key Release
	if (keycode == 126) // Up arrow key
		info->player->move_forward = 0;
	else if (keycode == 125) // Down arrow key
		info->player->move_backward = 0;
	else if (keycode == 123) // Left arrow key
		info->player->rotate_left = 0;
	else if (keycode == 124) // Right arrow key
		info->player->rotate_right = 0;

	return (0);
}

// void	move_object(t_player *player, t_cub *info)
// {
// 	float	x;
// 	float	y;

// 	x = player->x;
// 	y = player->y;
// 	if (player->move_forward)
// 	{
// 		player->x += MOVE_SPEED * cos(player->rotation_angle);
// 		player->y += MOVE_SPEED * sin(player->rotation_angle);
// 		if (has_wall(player->x, player->y, info))
// 		{
// 			player->x = x;
// 			player->y = y;
// 		}
// 	}
// 	else if (player->move_backward)
// 	{
// 		player->x -= MOVE_SPEED * cos(player->rotation_angle);
// 		player->y -= MOVE_SPEED * sin(player->rotation_angle);
// 		if (has_wall(player->x, player->y, info))
// 		{
// 			player->x = x;
// 			player->y = y;
// 		}
// 	}
// 	else if (player->rotate_right)
// 		player->rotation_angle += ROTATION_SPEED;
// 	else if (player->rotate_right)
// 		player->rotation_angle -= ROTATION_SPEED;
// }

int	move_and_draw(void *param)
{
	t_cub	*info;

	info = (t_cub *)param;
	info->img = mlx_new_image(info->mlx, COL * G_SIZE, ROW * G_SIZE);
	info->addr = mlx_get_data_addr(info->img, &info->bits_per_pixel, \
		&info->line_length, &info->endian);

	draw_map(info, info->player->map);

	move_object(info->player, info);

	draw_rays(info);

	draw_player(info, info->player);

	mlx_clear_window(info->mlx, info->mlx_win);
	mlx_put_image_to_window(info->mlx, info->mlx_win, info->img, 0, 0);
	mlx_destroy_image(info->mlx, info->img);
	return (0);
}

int	main(int ac, char **av)
{
	t_cub		info;
	t_player	player;
	char *map[] = {
        "111111111111111",
        "100000000000101",
        "100101000000101",
        "111110000010101",
        "100000000010101",
        "100000001101101",
        "100000000000001",
        "1000000N0000001",
        "111111000111101",
        "100000000000001",
        "111111111111111"
	};
	info.player = &player;
	init_player(&player, map);
	info.mlx = mlx_init();
	info.mlx_win = mlx_new_window(info.mlx, COL * G_SIZE, \
		ROW * G_SIZE, "Cub3D");
	// info.img = mlx_new_image(info.mlx, COL * G_SIZE, ROW * G_SIZE);
	// info.addr = mlx_get_data_addr(info.img, &info.bits_per_pixel, \
	// 	&info.line_length, &info.endian);
	mlx_hook(info.mlx_win, 17, 0, close_win, &info);
	mlx_hook(info.mlx_win, 2, 0, handle_keypress, &info);
	mlx_hook(info.mlx_win, 3, 0, handle_keyrelease, &info);
	mlx_loop_hook(info.mlx, move_and_draw, &info);
	mlx_loop(info.mlx);
	// mlx_hook(info.mlx_win, 2, 0, moves, &info);
	return (0);
}
