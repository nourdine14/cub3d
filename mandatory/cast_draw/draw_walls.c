/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_walls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 15:07:23 by nakebli           #+#    #+#             */
/*   Updated: 2023/08/20 20:43:29 by oaboulgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

bool	ray_lookig_left(double angle)
{
	if (angle < M_PI_2 || angle > 3 * M_PI_2)
		return (false);
	return (true);
}

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

int	is_door_face(t_cub *info, t_ray *ray)
{
	if ((ray->xhit < ray->yhit && \
			((has_wall((floor(ray->ix / G_SIZE) * G_SIZE) - 1, \
			ray->iy - 1, info) && \
			has_wall((ceil(ray->ix / G_SIZE) * G_SIZE) + 1, ray->iy - 1, \
			info)) || (has_wall((floor(ray->ix / G_SIZE) * G_SIZE) - 1, \
			ray->iy + 1, info) && has_wall((ceil(ray->ix / G_SIZE) * G_SIZE) \
			+ 1, ray->iy + 1, info)))) || (ray->yhit < ray->xhit && \
			((has_wall(ray->ix - 1, (floor(ray->iy / G_SIZE) * G_SIZE) \
			- 1, info) && has_wall(ray->ix - 1, (ceil(ray->iy / G_SIZE) * \
			G_SIZE) + 1, info)) || (has_wall(ray->ix + 1, (floor(ray->iy / \
			G_SIZE) * G_SIZE) - 1, info) && has_wall(ray->ix + 1, (ceil(ray->iy \
			/ G_SIZE) * G_SIZE) + 1, info)))))
		return (1);
	return (0);
}

void	draw_wall(t_cub *info, t_ray *ray, float ray_angle, int i)
{
	float	wall_projected;
	t_img	img;

	get_distance(ray, info, ray_angle);
	wall_projected = (25000 / ray->ray_dist);
	if (wall_projected > 2000)
		wall_projected = 2000;
	img = get_img_side(ray, info, ray_angle);
	info->x = i;
	info->y = (info->player->middle_of_screen) - (wall_projected);
	info->height = 2 * wall_projected;
	draw_line_of_texture(*info, &img, *ray);
}
