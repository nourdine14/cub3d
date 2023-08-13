/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   casting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 04:52:06 by oaboulgh          #+#    #+#             */
/*   Updated: 2023/08/13 17:22:31 by oaboulgh         ###   ########.fr       */
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

void	draw_line_of_texture(int x, int y, int	width, int height, 
		t_cub *info, t_img *img, t_ray ray)
{
	int		j;
	int		offset;
	int		color;
	int		offsetx;
	float	step;
	float	ycount;
	float	xcount;
	unsigned int	*t;

	(void)img;
	(void)ray;
	(void)width;
	j = 0;
	step = (float)img->height / height;
	if (ray.xhit < ray.yhit)
		offsetx = (int)ray.ix % G_SIZE;
	else
		offsetx = (int)ray.iy % G_SIZE;
	ycount = 0;
	xcount = img->width / G_SIZE;
	t = (unsigned int *)(img->addr);
	while (j < height)
	{
		offset = ((int)ycount * img->height + ((offsetx * (int)xcount)));
		
		color = t[offset];
		if (x >= 0 && y >= 0 && x < G_SIZE * COL && y < G_SIZE * ROW)
			my_mlx_pixel_put(&info->img, x, y, color);
		j++;
		y++;
		ycount += step;
	}
}

float	diff_of_two_points(float x, float y, float x1, float y1)
{
	return (sqrt((x1 - x) * (x1 - x) + (y1 - y) * (y1 - y)));
}

void	horizontale(t_cub *info, t_ray *ray, float ray_angle)
{
	// y of first intersection with wall
	ray->yinter = (ceil(info->player->y / G_SIZE) * G_SIZE);
	if (ray_lookig_up(ray_angle))
		ray->yinter -= G_SIZE;
	ray->xinter = info->player->x + (ray->yinter - info->player->y) / tan(ray_angle);
	
	
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
	while (IX >= 0 && IX < long_line(info->player->map) * G_SIZE && IY >= 0 && IY < height_of_map(info->player->map) * G_SIZE)
	{
		if (has_wall(IX, IY, info))
		{
			if (ray_lookig_up(ray_angle))
				IY++;
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
	int k = long_line(info->player->map);
	int c = height_of_map(info->player->map);
	while (ray->ix >= 0 && ray->ix < k * G_SIZE && ray->iy >= 0 && ray->iy < c * G_SIZE)
	{
		if (has_wall(ray->ix, ray->iy, info))
		{
			if (ray_lookig_left(ray_angle))
				ray->ix++;
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

void	draw_wall(t_cub *info, t_ray *ray, float ray_angle, int i)
{
	(void)i;
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
	ray->ray_dist = cos(fabs(ray_angle - info->player->rotation_angle)) * ray->ray_dist;
	float	wall_projected;
	wall_projected = (25000 / ray->ray_dist);
	t_img img;

	if (ray->xhit < ray->yhit)
	{
		if (ray_lookig_up(ray_angle))
			img = info->side1;
		else
			img = info->side2;
	}
	else
	{
		if (ray_lookig_left(ray_angle))
			img = info->side3;
		else
			img = info->side4;
	}
	if ((is_door(ray->ix, ray->iy, info)))
	{
		if ((ray->xhit < ray->yhit && \
			((has_wall((floor(ray->ix / G_SIZE) * G_SIZE) - 1, ray->iy - 1 , info) && \
		 	has_wall((ceil(ray->ix / G_SIZE) * G_SIZE) + 1, ray->iy - 1 , info)) || \
			(has_wall((floor(ray->ix / G_SIZE) * G_SIZE) - 1, ray->iy + 1 , info) && \
		 	has_wall((ceil(ray->ix / G_SIZE) * G_SIZE) + 1, ray->iy + 1 , info))) ) || \
			(ray->yhit < ray->xhit && \
			((has_wall(ray->ix - 1, (floor(ray->iy / G_SIZE) * G_SIZE) - 1, info) && \
			has_wall(ray->ix - 1, (ceil(ray->iy / G_SIZE) * G_SIZE) + 1, info)) || \
			(has_wall(ray->ix + 1, (floor(ray->iy / G_SIZE) * G_SIZE) - 1, info) && \
			has_wall(ray->ix + 1, (ceil(ray->iy / G_SIZE) * G_SIZE) + 1, info)))))
		{
			img = info->door;	
		}
		else
		{
			img = info->doorside;
		}
	}
	draw_line_of_texture(i, (info->player->middle_of_screen) - (wall_projected), \
	WALL_WIDTH, 2 * wall_projected, info, &img, *ray);
}

void	cast_rays(t_cub *info, float ray_angle, int i)
{
	t_ray	ray;

	(void)i;
	//*Horizontale*//
	horizontale(info, &ray, ray_angle); // calculate horizontale hit with wall

	//*Verticale*//
	verticale(info, &ray, ray_angle); // calculate vertical hit with wall
	
	// choose short distance that hit wall and draw a vertical wall on ray_hit(x, y)
	draw_wall(info, &ray, ray_angle, i);
	
	// dda(info->player->x, info->player->y, ray.ix, ray.iy, info, 0xff6666);
}
