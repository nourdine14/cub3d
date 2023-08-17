/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 05:14:00 by oaboulgh          #+#    #+#             */
/*   Updated: 2023/08/13 13:02:30 by oaboulgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_player2(t_cub *info, float dx, float dy)
{
	if (info->player->move_forward_l)
		info->player->x1 += dy;
	if (info->player->move_forward_l)
		info->player->y1 -= dx;
	if (info->player->move_forward_r)
		info->player->x1 -= dy;
	if (info->player->move_forward_r)
		info->player->y1 += dx;
	if (info->player->move_forward)
		info->player->x1 += dx;
	if (info->player->move_forward)
		info->player->y1 += dy;
	if (info->player->move_backward)
		info->player->x1 -= dx;
	if (info->player->move_backward)
		info->player->y1 -= dy;
	info->player->x = info->player->x1;
	info->player->y = info->player->y1;
}

void move_player(t_player *player, t_cub *info)
{
	float	angle;
	float	dx;
	float	dy;
	static int	counter;

	if (!player->shot)
		counter = 0;
	angle = player->rotation_angle;
	info->player->x1 = player->x;
	info->player->y1 = player->y;
	angle = scale_angle(angle);
	dx = cos(angle) * MOVE_SPEED;
	dy = sin(angle) * MOVE_SPEED;
	move_player2(info, dx, dy);
	if (player->rotate_left)
		player->rotation_angle -= ROTATION_SPEED;
	if (player->rotate_right)
		player->rotation_angle += ROTATION_SPEED;

	counter++;
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

void	draw_hp_len(t_cub *info, int hp)
{
	int	i;
	int	j;

	j = 750;
	i = 50;
	while (i < (10 + 50))
	{
		j = 750;
		while (j < (hp + 750))
		{
			if (j >= 0 && j <= COL * G_SIZE && i >= 0 && i <= ROW * G_SIZE)
				my_mlx_pixel_put(&info->img, j, i, 0xff0000);
			j++;
		}
		i++;
	}
	j = 750;
	while (j < (hp + 750))
	{
		if (j >= 0 && j <= COL * G_SIZE && i >= 0 && i <= ROW * G_SIZE)
			my_mlx_pixel_put(&info->img, j, 49, 0xffffff);
		if (j >= 0 && j <= COL * G_SIZE && i >= 0 && i <= ROW * G_SIZE)
			my_mlx_pixel_put(&info->img, j, 48, 0xffffff);
		if (j >= 0 && j <= COL * G_SIZE && i >= 0 && i <= ROW * G_SIZE)
			my_mlx_pixel_put(&info->img, j, 60, 0xffffff);
		if (j >= 0 && j <= COL * G_SIZE && i >= 0 && i <= ROW * G_SIZE)
			my_mlx_pixel_put(&info->img, j, 61, 0xffffff);
		
		j++;
	}
	i = 48;
	while(i < 62)
	{
		if (j >= 0 && j <= COL * G_SIZE && i >= 0 && i <= ROW * G_SIZE)
			my_mlx_pixel_put(&info->img, 750, i, 0xffffff);
		if (j >= 0 && j <= COL * G_SIZE && i >= 0 && i <= ROW * G_SIZE)
			my_mlx_pixel_put(&info->img, 900, i, 0xffffff);
		if (j >= 0 && j <= COL * G_SIZE && i >= 0 && i <= ROW * G_SIZE)
			my_mlx_pixel_put(&info->img, 749, i, 0xffffff);
		if (j >= 0 && j <= COL * G_SIZE && i >= 0 && i <= ROW * G_SIZE)
			my_mlx_pixel_put(&info->img, 901, i, 0xffffff);
		i++;
	}
}

void	full_images3(t_cub *info, int x, int y)
{
	info->side4.img_ptr = mlx_xpm_file_to_image(info->mlx, "textures/side4.xpm", &x, &y);
	if (!info->side4.img_ptr)
	{
		printf("Error image couldn't load\n");
		exit (1);
	}
	info->side4.addr = mlx_get_data_addr(info->side4.img_ptr, &info->side4.bpp, &info->side4.line_len, &info->side4.endian);
	info->side4.height = y;
	info->side4.width = x;
}

void	full_images2(t_cub *info, int x, int y)
{
	info->side2.img_ptr = mlx_xpm_file_to_image(info->mlx, "textures/sd1.xpm", &x, &y);
	if (!info->side2.img_ptr)
	{
		printf("Error image couldn't load\n");
		exit (1);
	}
	info->side2.addr = mlx_get_data_addr(info->side2.img_ptr, &info->side2.bpp, &info->side2.line_len, &info->side2.endian);
	info->side2.height = y;
	info->side2.width = x;
	info->side3.img_ptr = mlx_xpm_file_to_image(info->mlx, "textures/side3.xpm", &x, &y);
	if (!info->side3.img_ptr)
	{
		printf("Error image couldn't load\n");
		exit (1);
	}
	info->side3.addr = mlx_get_data_addr(info->side3.img_ptr, &info->side3.bpp, &info->side3.line_len, &info->side3.endian);
	info->side3.height = y;
	info->side3.width = x;
	full_images3(info, x, y);
}

void	full_images(t_cub *info)
{
	int	x;
	int	y;

	info->img.img_ptr = mlx_new_image(info->mlx, long_line(info->player->map) * G_SIZE, \
		height_of_map(info->player->map) * G_SIZE);
	info->img.addr = mlx_get_data_addr(info->img.img_ptr, &info->img.bpp, \
		&info->img.line_len, &info->img.endian);

	info->side1.img_ptr = mlx_xpm_file_to_image(info->mlx, "textures/s1.xpm", &x, &y);
	if (!info->side1.img_ptr)
	{
		printf("Error image couldn't load\n");
		exit (1);
	}
	info->side1.height = y;
	info->side1.width = x;
	info->side1.addr = mlx_get_data_addr(info->side1.img_ptr, &info->side1.bpp, &info->side1.line_len, &info->side1.endian);
	// full_images2(info, x, y);
}

int	move_and_draw(void *param)
{
	t_cub	*info;
	// struct timeval tp;
	// static double oldtime;
	// gettimeofday(&tp, NULL);
	// double time = tp.tv_usec;
	// double frame_time = (time - oldtime);
	// printf("FPS: %f\n", 1000000 / frame_time);
	info = (t_cub *)param;
	full_images(info);
	color_background(info);
	draw_rays(info);
	draw_map(info, info->player->map);
	draw_player(info, info->player);
	move_player(info->player, info);
	
	mlx_clear_window(info->mlx, info->mlx_win);
	mlx_put_image_to_window(info->mlx, info->mlx_win, info->img.img_ptr, 0, 0);
	mlx_put_image_to_window(info->mlx, info->mlx_win, info->gun1.img_ptr, 450, 185);
	mlx_destroy_image(info->mlx, info->img.img_ptr);
	// oldtime = time;
	return (0);
}
