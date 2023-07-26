/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 10:12:10 by oaboulgh          #+#    #+#             */
/*   Updated: 2023/07/22 21:12:13 by oaboulgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <stdio.h>
// #include "MLX42/MLX42.h"
// #include "/users/oaboulgh/Desktop/MLX42/include/MLX42/MLX42
#define WIDTH 720
#define HEIGHT 480

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

void my_keyhook(mlx_key_data_t keydata, void* param)
{
	// If we PRESS the 'J' key, print "Hello".
	if (keydata.key == MLX_KEY_J && keydata.action == MLX_PRESS)
		puts("Hello ");

	// If we RELEASE the 'K' key, print "World".
	if (keydata.key == MLX_KEY_K && keydata.action == MLX_RELEASE)
		puts("World");

	// If we HOLD the 'L' key, print "!".
	if (keydata.key == MLX_KEY_L && keydata.action == MLX_REPEAT)
		puts("!");
}

int32_t	main(void)
{
	mlx_t* mlx;

	if (!(mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true)))
		return (EXIT_FAILURE);

	mlx_key_hook(mlx, &my_keyhook, NULL);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
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