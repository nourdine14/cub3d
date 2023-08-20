/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_walls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 15:07:23 by nakebli           #+#    #+#             */
/*   Updated: 2023/08/20 16:05:54 by oaboulgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	get_distance(t_ray *ray, t_cub *info, float ray_angle)
{
	if (ray->b)
		ray->xhit = diff_of_two_points(info->player->x, info->player->y, \
			ray->xherizontalle_hit_wall, ray->yherizontalle_hit_wall);
	else
		ray->xhit = MAXFLOAT;
	if (ray->a)
		ray->yhit = diff_of_two_points(info->player->x, info->player->y, \
			ray->xvertical_hit_wall, ray->yvertical_hit_wall);
	else
		ray->yhit = MAXFLOAT;
	if (ray->xhit < ray->yhit)
	{
		ray->ix = ray->xherizontalle_hit_wall;
		ray->iy = ray->yherizontalle_hit_wall;
		ray->ray_dist = ray->xhit;
	}
	else
	{
		ray->ix = ray->xvertical_hit_wall;
		ray->iy = ray->yvertical_hit_wall;
		ray->ray_dist = ray->yhit;
	}
	ray->ray_dist = \
	cos(ray_angle - info->player->rotation_angle) * ray->ray_dist;
}

static t_img	get_img_side(t_ray *ray, t_cub *info, float ray_angle)
{
	if (ray->xhit < ray->yhit)
	{
		if (ray_lookig_up(ray_angle))
			return (info->side1);
		else
			return (info->side2);
	}
	else
	{
		if (ray_lookig_left(ray_angle))
			return (info->side3);
		else
			return (info->side4);
	}
}

int	is_door_face(t_cub *info, t_ray *ray, float ray_angle)
{
	int	k;
	int	l;

	if (ray_lookig_left(ray_angle))
		k = -1;
	else
		k = 1;
	if (ray_lookig_up(ray_angle))
		l = -1;
	else
		l = 1;
	if (ray->xhit <= ray->yhit && has_wall_only(ray->ix, ray->iy + l, info))
		return (0);
	if (ray->yhit < ray->xhit && has_wall_only(ray->ix + k, ray->iy, info))
		return (0);
	return (1);
}

void	draw_wall(t_cub *info, t_ray *ray, float ray_angle, int i)
{
	float	wall_projected;
	t_img	img;

	get_distance(ray, info, ray_angle);
	wall_projected = (25000 / ray->ray_dist);
	img = get_img_side(ray, info, ray_angle);
	if ((is_door(ray->ix, ray->iy, info)))
	{
		if (is_door_face(info, ray, ray_angle))
			img = info->door;
		else
			img = info->doorside;
	}
	info->x = i;
	info->y = (info->player->middle_of_screen) - (wall_projected);
	info->height = 2 * wall_projected;
	draw_line_of_texture(*info, &img, *ray);
}
