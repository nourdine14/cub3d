/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   casting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakebli <nakebli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 04:52:06 by oaboulgh          #+#    #+#             */
/*   Updated: 2023/08/11 20:21:10 by nakebli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	draw_circle(t_cub *info, t_player *player)
{
	int	a;
	int	b;
	int	n;
	int	i;
	int	j;

	n = (2 * player->radius) + 1;
	a = 100;
	b = 100;
	i = 0;
	while (i < n)
	{
		j = 0;
		while (j < n)
		{
			a = i - player->radius;
			b = j - player->radius;
			if ((a * a) + (b * b) <= player->radius * player->radius + 1)
				if ((a + 100) >= 0 && (b + 100) >= 0 && \
				(b + 100) <= ROW * G_SIZE && (a + 100) <= COL * G_SIZE)
					my_mlx_pixel_put(&info->img, \
					(a + 100), (b + 100), 0xcc6600);
			j++;
		}
		i++;
	}
}

float	diff_of_two_points(float x, float y, float x1, float y1)
{
	return (sqrt((x1 - x) * (x1 - x) + (y1 - y) * (y1 - y)));
}

void	ft_put_pixel(t_cub info, t_img *img, int offset)
{
	if (info.x >= 0 && info.y >= 0 && info.x < G_SIZE * COL && \
	info.y < G_SIZE * ROW)
		my_mlx_pixel_put(&info.img, info.x, info.y, \
		*(int *)(img->addr + offset));
}

void	draw_line_of_texture(t_cub info, t_img *img, t_ray ray)
{
	int		i;
	int		offset;
	float	offsetx;
	float	step;
	float	ycount;

	i = 0;
	step = (float)img->height / info.height;
	if (ray.xhit < ray.yhit)
		offsetx = (int)ray.ix % G_SIZE;
	else
		offsetx = (int)ray.iy % G_SIZE;
	while (i < WALL_WIDTH)
	{
		ycount = 0;
		while (info.height--)
		{
			offset = ((int)ycount * img->line_len) + (offsetx * (img->bpp / 2));
			ft_put_pixel(info, img, offset);
			info.y++;
			ycount += step;
		}
		i++;
		info.x++;
	}
}

void	cast_rays(t_cub *info, float ray_angle, int i)
{
	t_ray	ray;

	horizontale(info, &ray, ray_angle);
	verticale(info, &ray, ray_angle);
	draw_wall(info, &ray, ray_angle, i);
}
