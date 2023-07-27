/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   casting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 04:52:06 by oaboulgh          #+#    #+#             */
/*   Updated: 2023/07/26 07:11:34 by oaboulgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	ray_lookig_up(double angle)
{
	if (angle < M_PI && angle > 0)
		return (false);
	return (true);
}

bool	ray_lookig_left(double angle)
{
	if (angle < M_PI_2 || angle > 3 * M_PI_2)
		return (false);
	return (true);
}

void	draw_rect(float x, float y, int	width, int height, 
		t_cub *info, int color)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < width)
	{
		j = 0;
		while (j < height)
		{
			my_mlx_pixel_put(info, x, y, color);
			j++;
			y++;
		}
		x++;
		i++;
	}
}

float	diff_of_two_points(float x, float y, float x1, float y1)
{
	return (sqrt((x1 - x) * (x1 - x) + (y1 - y) * (y1 - y)));
}

void	horizontale(t_cub *info, t_ray *ray, float ray_angle)
{
	ray->yinter = (floor(info->player->y / G_SIZE) * G_SIZE);
	if (!ray_lookig_up(ray_angle))
		ray->yinter += G_SIZE;
	ray->xinter = info->player->x + (ray->yinter - info->player->y)/ tan(ray_angle);
	
	
	ray->ystep = G_SIZE;
	ray->xstep = G_SIZE / tan(ray_angle);

	if (ray_lookig_up(ray_angle))
		ray->ystep *= -1;
	if (ray_lookig_up(ray_angle))
		ray->xstep *= -1;
	float	IX = ray->xinter;
	float	IY = ray->yinter;
	ray->b = false;
	if (ray_lookig_up(ray_angle))
		IY--;
	while (IX >= 0 && IX <= COL * G_SIZE && IY >= 0 && IY <= ROW * G_SIZE)
	{
		if (has_wall(IX, IY, info))
		{
			ray->b = true;
			ray->xherizontalle_hit_wall = IX;
			ray->yherizontalle_hit_wall = IY;
			break;
		}
		else
		{
			IX += ray->xstep;
			IY += ray->ystep;
		}
	}
}

void	verticale(t_cub *info, t_ray *ray, float ray_angle)
{
	ray->xinter = (floor(info->player->x / G_SIZE) * G_SIZE);
	if (!ray_lookig_left(ray_angle))
		ray->xinter += G_SIZE;
	ray->yinter = info->player->y + (ray->xinter - info->player->x) * tan(ray_angle);
	
	
	ray->xstep = G_SIZE;
	ray->ystep = G_SIZE * tan(ray_angle);

	if (ray_lookig_left(ray_angle))
		ray->ystep *= -1;
	if (ray_lookig_left(ray_angle))
		ray->xstep *= -1;
	ray->ix = ray->xinter;
	ray->iy = ray->yinter;
	ray->a = false;
	if (ray_lookig_left(ray_angle))
		ray->ix--;
	while (ray->ix >= 0 && ray->ix <= COL * G_SIZE && ray->iy >= 0 && ray->iy <= ROW * G_SIZE)
	{
		if (has_wall(ray->ix, ray->iy, info))
		{
			ray->a = true;
			ray->xvertical_hit_wall = ray->ix;
			ray->yvertical_hit_wall = ray->iy;
			break;
		}
		else
		{
			ray->ix += ray->xstep;
			ray->iy += ray->ystep;
		}
	}
}

void	draw_wall(t_cub *info, t_ray ray, float ray_angle, int i)
{
	float	xhit;
	float	yhit;
	float	ray_dist;
	if (ray.b)
		xhit = diff_of_two_points(info->player->x, info->player->y, \
			ray.xherizontalle_hit_wall, ray.yherizontalle_hit_wall);
	else
		xhit = MAXFLOAT;
	if (ray.a)
		yhit = diff_of_two_points(info->player->x, info->player->y, \
			ray.xvertical_hit_wall, ray.yvertical_hit_wall);
	else
		yhit = MAXFLOAT;
	if (xhit < yhit)
	{
		ray.ix = ray.xherizontalle_hit_wall;
		ray.iy = ray.yherizontalle_hit_wall;
		ray_dist = xhit;
	}
	else
	{
		ray.ix = ray.xvertical_hit_wall;
		ray.iy = ray.yvertical_hit_wall;
		ray_dist = yhit;
	}
	ray_dist = cos(ray_angle - info->player->rotation_angle) * ray_dist;
	// float	ray_dist2 = (G_SIZE * ROW / 4) / tan(VIEW_ANGLE * DG / 2);
	// float	wall_projected = (G_SIZE / ray_dist) * ray_dist2;
	
	float	wall_projected = (15000 / ray_dist);
	// printf("wall projection %f\n", wall_projected);
	if (wall_projected > G_SIZE * ROW / 2)
		wall_projected = G_SIZE * ROW / 2;
	// int	color;

	draw_rect(i, (G_SIZE * ROW / 2) - (wall_projected), \
	WALL_WIDTH, 2 * wall_projected, info, 0xd2a679);
}

void	cast_rays(t_cub *info, float ray_angle, int i)
{
	t_ray	ray;

	//*Horizontale*//
	horizontale(info, &ray, ray_angle);

	//*Verticale*//
	verticale(info, &ray, ray_angle);

	draw_wall(info, ray, ray_angle, i);
}
