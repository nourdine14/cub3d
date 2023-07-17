/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 10:12:10 by oaboulgh          #+#    #+#             */
/*   Updated: 2023/07/14 22:51:47 by oaboulgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct s_info
{
	void			*mlx;
	void			*mlx_win;
	float	x0;
	float	y0;
	float	x1;
	float	y1;
	float	rot;
}	t_info;

void dda(float X0, float Y0, float X1, float Y1, t_info *info)
{
	// calculate dx & dy
	float	s;
	float	s1;

	s = X1;
	s1 = Y1;
	X1 = (s * cos(info->rot) - Y1 * sin(info->rot));
	Y1 = (s * sin(info->rot) + Y1 * cos(info->rot));
	int dx = X1 - X0;
	int dy = Y1 - Y0;

	// calculate steps required for generating pixels
	int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);

	// calculate increment in x & y for each steps
	float Xinc = dx / (float)steps;
	float Yinc = dy / (float)steps;

	// Put pixel for each step
	float X = X0;
	float Y = Y0;
	for (int i = 0; i <= steps; i++) {
		mlx_pixel_put(info->mlx, info->mlx_win, X, Y, 0xcc66600); // put pixel at (X,Y)
		X += Xinc; // increment in x at each step
		Y += Yinc; // increment in y at each step
	}
}

int	func(int keycode, void *param)
{
	t_info *info;

	info = (t_info *)param;
	if (keycode == 124)
	{
		info->rot += 0.5;
		mlx_clear_window(info->mlx, info->mlx_win);
		dda(info->x0, info->y0, info->x1, info->y1, info);
	}
	if (keycode == 123)
	{
		info->rot -= 0.5;
		mlx_clear_window(info->mlx, info->mlx_win);
		dda(info->x0, info->y0, info->x1, info->y1, info);
	}
	return (0);
}

int	main()
{
	t_info	info;
	info.x0 = 500;
	info.y0 = 500;
	info.x1 = 50;
	info.y1 = 50;
	info.rot = M_PI_2;

	info.mlx = mlx_init();
	info.mlx_win = mlx_new_window(info.mlx, 1000, 1000, "line");
	dda(info.x0, info.y0, info.x1, info.y1, &info);
	mlx_hook(info.mlx_win, 2, 0, func, &info);
	mlx_loop(info.mlx);
}

/*
int	moves(int keycode, void *param)
{
	t_cub	*info;
	float	x;
	float	y;

	info = (t_cub *)param;
	x = info->player->x;
	y = info->player->y;
	if (keycode == 53)
	{
		mlx_destroy_window(info->mlx, info->mlx_win);
		exit (0);
	}
	if (keycode == 125)
	{
		info->player->x += MOVE_SPEED * cos(info->player->rotation_angle);
		info->player->y += MOVE_SPEED * sin(info->player->rotation_angle);
		if (has_wall(info->player->x, info->player->y, info))
			return (info->player->x = x, info->player->y = y, 0);
	}
	else if (keycode == 126)
	{
		info->player->x -= MOVE_SPEED * cos(info->player->rotation_angle);
		info->player->y -= MOVE_SPEED * sin(info->player->rotation_angle);
		if (has_wall(info->player->x, info->player->y, info))
			return (info->player->x = x, info->player->y = y, 0);
	}
	else if (keycode == 124)
		info->player->rotation_angle += ROTATION_SPEED;
	else if (keycode == 123)
		info->player->rotation_angle -= ROTATION_SPEED;
	mlx_destroy_image(info->mlx, info->img);
	mlx_clear_window(info->mlx, info->mlx_win);
	info->img = mlx_new_image(info->mlx, COL * G_SIZE, ROW * G_SIZE);
	info->addr = mlx_get_data_addr(info->img, &info->bits_per_pixel, \
		&info->line_length, &info->endian);
	draw_map(info, info->player->map);
	draw_player(info, info->player);
	draw_rays(info);
	return (0);
}
*/