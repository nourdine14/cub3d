/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   horizontal_vertical.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakebli <nakebli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 23:35:12 by nakebli           #+#    #+#             */
/*   Updated: 2023/08/11 12:51:00 by nakebli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	init_first_horizontal_inter(t_ray *ray, t_cub *info, float ray_agl)
{
	ray->yinter = (ceil(info->player->y / G_SIZE) * G_SIZE);
	if (ray_lookig_up(ray_agl))
		ray->yinter -= G_SIZE;
	ray->xinter = (info->player->x + \
	(ray->yinter - info->player->y) / tan(ray_agl));
	ray->ystep = G_SIZE;
	ray->xstep = G_SIZE / tan(ray_agl);
	if (ray_lookig_up(ray_agl))
		ray->ystep *= -1;
	if (ray_lookig_up(ray_agl))
		ray->xstep *= -1;
}

static void	init_first_vertical_inter(t_ray *ray, t_cub *info, float ray_angle)
{
	ray->xinter = (floor(info->player->x / G_SIZE) * G_SIZE);
	if (!ray_lookig_left(ray_angle))
		ray->xinter += G_SIZE;
	ray->yinter = info->player->y + \
	(ray->xinter - info->player->x) * tan(ray_angle);
	ray->xstep = G_SIZE;
	ray->ystep = G_SIZE * tan(ray_angle);
	if (ray_lookig_left(ray_angle))
		ray->ystep *= -1;
	if (ray_lookig_left(ray_angle))
		ray->xstep *= -1;
}

static void	get_wall_inter_cardinals(t_ray *ray, float ray_angle, int flag)
{
	if (flag == 1)
	{
		if (ray_lookig_left(ray_angle))
			ray->ix++;
		ray->a = true;
		ray->xvertical_hit_wall = ray->ix;
		ray->yvertical_hit_wall = ray->iy;
	}
	if (flag == 2)
	{
		if (ray_lookig_up(ray_angle))
			ray->hiy++;
		ray->b = true;
		ray->xherizontalle_hit_wall = ray->hix;
		ray->yherizontalle_hit_wall = ray->hiy;
	}
}

void	horizontale(t_cub *info, t_ray *ray, float ray_angle)
{
	init_first_horizontal_inter(ray, info, ray_angle);
	ray->hix = ray->xinter;
	ray->hiy = ray->yinter;
	ray->b = false;
	if (ray_lookig_up(ray_angle))
		ray->hiy--;
	while (ray->hix >= 0 && ray->hix < long_line(info->player->map) * G_SIZE \
	&& ray->hiy >= 0 && ray->hiy < height_of_map(info->player->map) * G_SIZE)
	{
		if (has_wall(ray->hix, ray->hiy, info))
		{
			get_wall_inter_cardinals(ray, ray_angle, 2);
			break ;
		}
		else
		{
			ray->hix += ray->xstep;
			ray->hiy += ray->ystep;
		}
	}
}

void	verticale(t_cub *info, t_ray *ray, float ray_angle)
{
	int	k;
	int	c;

	init_first_vertical_inter(ray, info, ray_angle);
	ray->ix = ray->xinter;
	ray->iy = ray->yinter;
	ray->a = false;
	if (ray_lookig_left(ray_angle))
		ray->ix--;
	k = long_line(info->player->map);
	c = height_of_map(info->player->map);
	while (ray->ix >= 0 && ray->ix < k * G_SIZE && ray->iy >= 0 \
	&& ray->iy < c * G_SIZE)
	{
		if (has_wall(ray->ix, ray->iy, info))
		{
			get_wall_inter_cardinals(ray, ray_angle, 1);
			break ;
		}
		else
		{
			ray->ix += ray->xstep;
			ray->iy += ray->ystep;
		}
	}
}
