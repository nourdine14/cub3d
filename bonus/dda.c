/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 19:33:34 by oaboulgh          #+#    #+#             */
/*   Updated: 2023/08/17 17:26:04 by oaboulgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	dda(int X1, int Y1, t_cub *info, int color)
{
	int		steps;
	float	x;
	float	y;
	float	y_inc;
	float	x_inc;

	x = 100;
	y = 100;
	if (abs(X1 - 100) > abs(Y1 - 100))
		steps = abs(X1 - 100);
	else
		steps = abs(Y1 - 100);
	x_inc = (X1 - 100) / (float)steps;
	y_inc = (Y1 - 100) / (float)steps;
	while (steps)
	{
		if (x < 0 || x >= G_SIZE * COL || y < 0 || y >= G_SIZE * ROW)
			return ;
		my_mlx_pixel_put(&info->img, x, y, color);
		x += x_inc;
		y += y_inc;
		steps--;
	}
}

static void	color_half(t_cub *info, int j, int color)
{
	int	i;

	while (j < ROW * G_SIZE)
	{
		i = 0;
		while (i < COL * G_SIZE)
		{
			if (i >= 0 && j >= 0 && i < G_SIZE * COL && j < G_SIZE * ROW)
				my_mlx_pixel_put(&info->img, i, j, color);
			i++;
		}
		j++;
	}
}

void	color_background(t_cub *info)
{
	color_half(info, 0, combine_rgb_colors(info->info->f[0], \
		info->info->f[1], info->info->f[2]));
	// printf("floor %d %d %d\n", info->info->f[0], info->info->f[1], info->info->f[2]);
	// printf("ceil %d %d %d\n", info->info->c[0], info->info->c[1], info->info->c[2]);
	// exit (0);
	color_half(info, info->player->middle_of_screen, \
		combine_rgb_colors(info->info->c[0], \
		info->info->c[1], info->info->c[2]));
}

void	my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_len + x * (data->bpp / 8));
	*(unsigned int *)dst = color;
}

int	combine_rgb_colors(int red, int green, int blue)
{
	return ((red << 16) | (green << 8) | blue);
}
