/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 12:39:05 by oaboulgh          #+#    #+#             */
/*   Updated: 2023/08/04 07:38:03 by oaboulgh         ###   ########.fr       */
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
	b = 100 - info->player->y * MINI_MAP_SCALE;
	while (map[i])
	{
		j = 0;
		a = 100 - info->player->x * MINI_MAP_SCALE;
		while (map[i][j] != '\n')
		{
			// if (map[i][j] == 'E')
			// {
				if (map[i][j] == '1')
					draw_square(info, a, b, 0xFFFFFF);
				else if (map[i][j] == ' ')
					draw_square(info, a, b, 0x000000);
				else
					draw_square(info, a, b, 0xccf2ff);
			// }
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


void	my_mlx_pixel_put(t_cub *data, int x, int y, int color)
{
	char	*dst;

	dst = data->img.addr + (y * data->img.line_len + x * (data->img.bpp / 8));
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
	// Key Press
	if (keycode == 53)
	{
		mlx_destroy_window(info->mlx, info->mlx_win);
		exit (0);
	}
	if (keycode == 126) // Up arrow key
		info->player->move_forward = 1;
	else if (keycode == 125) // Down arrow key
		info->player->move_backward = 1;
	else if (keycode == 123) // Left arrow key
		info->player->rotate_left = 1;
	else if (keycode == 124) // Right arrow key
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
				my_mlx_pixel_put(info, i, j, 0x99d6ff);
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
			if (i > 0 && j > 0 && i < G_SIZE * COL && j < G_SIZE * ROW)
				my_mlx_pixel_put(info, i, j, 0x737373);
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
		while (map[i][j] != '\n')
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

int	move_and_draw(void *param)
{
	t_cub	*info;
	int		x;
	int		y;


	info = (t_cub *)param;
	info->img.img_ptr = mlx_new_image(info->mlx, long_line(info->player->map) * G_SIZE, \
		height_of_map(info->player->map) * G_SIZE);
	info->img.addr = mlx_get_data_addr(info->img.img_ptr, &info->img.bpp, \
		&info->img.line_len, &info->img.endian);
	
	info->side1.img_ptr = mlx_xpm_file_to_image(info->mlx, "textures/side1.xpm", &x, &y);
	info->side1.addr = mlx_get_data_addr(info->side1.img_ptr, &info->side1.bpp, &info->side1.line_len, &info->side1.endian);
	info->side1.height = y;
	info->side1.width = x;
	info->side2.img_ptr = mlx_xpm_file_to_image(info->mlx, "textures/side1.xpm", &x, &y);
	info->side2.addr = mlx_get_data_addr(info->side2.img_ptr, &info->side2.bpp, &info->side2.line_len, &info->side2.endian);
	info->side2.height = y;
	info->side2.width = x;
	info->side3.img_ptr = mlx_xpm_file_to_image(info->mlx, "textures/side3.xpm", &x, &y);
	info->side3.addr = mlx_get_data_addr(info->side3.img_ptr, &info->side3.bpp, &info->side3.line_len, &info->side3.endian);
	info->side3.height = y;
	info->side3.width = x;
	info->side4.img_ptr = mlx_xpm_file_to_image(info->mlx, "textures/side3.xpm", &x, &y);
	info->side4.addr = mlx_get_data_addr(info->side4.img_ptr, &info->side4.bpp, &info->side4.line_len, &info->side4.endian);
	info->side4.height = y;
	info->side4.width = x;


	color_background(info);

	draw_rays(info);

	draw_map(info, info->player->map);
	
	draw_player(info, info->player);

	move_player(info->player, info);
	
	mlx_put_image_to_window(info->mlx, info->mlx_win, info->img.img_ptr, 0, 0);
	mlx_clear_window(info->mlx, info->mlx_win);
	mlx_put_image_to_window(info->mlx, info->mlx_win, info->img.img_ptr, 0, 0);
	mlx_destroy_image(info->mlx, info->img.img_ptr);
	// free(info->side1.addr);
	return (0);
}


int	handle_mouse_move(int x, int y, t_cub *info)
{
	int	dx;
	int	dy;
	
	dx = x - info->player->mouse_x;
	dy = y - info->player->mouse_y;

	info->player->mouse_x = x;
	info->player->mouse_y = y;
	if (x < G_SIZE * COL && y < G_SIZE * ROW && x > 0 && y > 0)
		info->player->rotation_angle += 0.005 * dx;
	if (x < G_SIZE * COL && y < G_SIZE * ROW && x > 0 && y > 0 && \
		dy > 0 && info->player->middle_of_screen > 100)
		info->player->middle_of_screen -= 3;
	if (x < G_SIZE * COL && y < G_SIZE * ROW && x > 0 && y > 0 && \
		dy < 0 && info->player->middle_of_screen < (G_SIZE * ROW - 100))
		info->player->middle_of_screen += 3;
	return (0);
}

int	main(int ac, char **av)
{
	t_cub		info;
	t_player	player;
	// int			colums;
	// int			rows;
	(void)av;
	(void)ac;
	char *map[] = {
        "111111111111111111111111111111111111111111111111111111111111\n",
		"100000000000000000001100000000001100000000000000000000000001\n",
		"100001110000000000001111000000001100000000000000000000000001\n",
		"100000E10000000000000000000000000000000000000000000000000001\n",
		"10000111000000000001111000000001111111000000000000000000011\n",
		"1000000000000000000000000000000000000000000000000000000000111\n",
		"11111111100000010001111110001111100011111110000000000000001\n",
		"10000111100000010001111110001111100111111110000010000000001\n",
		"1000000000000000000000000000000000011111111000011000011001111\n",
		"10000000000000000000000000000000000000000000000111111110001\n",
		"100000000000000000000000000000000000000000000000000000001111111\n",
		"100000000000000000000000000000000000000000000000000000000011\n",
		"11111010011110010011111010010000100001010001000100010000101\n",
		"10001010001010010010100010010000100001010001000100010000001\n",
		"10000000000000000000000000000000000000000000000000000000001\n",
		"10000000000000000000000000000000000000000000000000000000001\n",
		"111111111111111111111111111111111111111111111111111111111111\n",
		NULL
	};
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
