/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   casting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 04:52:06 by oaboulgh          #+#    #+#             */
/*   Updated: 2023/08/04 07:34:56 by oaboulgh         ###   ########.fr       */
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
	int		i;
	int		j;
	int		offset;
	int		color;
	float	offsetx;
	float	step;
	float	ycount;

	(void)img;
	(void)ray;
	(void)width;
	i = 0;
	step = (float)img->height / height;
	if (ray.xhit < ray.yhit)
		offsetx = (int)ray.ix % G_SIZE;
	else
		offsetx = (int)ray.iy % G_SIZE;
	while (i < width)
	{
		j = 0;
		ycount = 0;
		while (j < height)
		{
			offset = ((int)ycount * img->line_len) + (offsetx * (img->bpp / 2));
			color = *(int *)(img->addr + offset);
			if (x >= 0 && y >= 0 && x <= G_SIZE * COL && y <= G_SIZE * ROW)
				my_mlx_pixel_put(info, x, y, color);
			j++;
			y++;
			ycount += step;
		}
		i++;
		x++;
	}
}

float	diff_of_two_points(float x, float y, float x1, float y1)
{
	return (fabs(sqrt((x1 - x) * (x1 - x) + (y1 - y) * (y1 - y))));
}

void	horizontale(t_cub *info, t_ray *ray, float ray_angle)
{
	// y of first intersection with wall
	ray->yinter = (ceil(info->player->y / G_SIZE) * G_SIZE);
	if (ray_lookig_up(ray_angle))
		ray->yinter -= G_SIZE;
	
	ray->xinter = info->player->x + (ray->yinter - info->player->y) /  tan(ray_angle);
	
	
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
		if (has_wall(IX , IY, info))
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
	while (ray->ix >= 0 && ray->ix < long_line(info->player->map) * G_SIZE && ray->iy >= 0 && ray->iy < height_of_map(info->player->map) * G_SIZE)
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
		// if (ray_lookig_left(ray_angle))
		ray->ix = ray->xvertical_hit_wall;
		ray->iy = ray->yvertical_hit_wall;
		ray->ray_dist = ray->yhit;
	}
	ray->ray_dist = cos(ray_angle - info->player->rotation_angle) * ray->ray_dist;
	
	// printf("ray dis = %f\n", ray->ray_dist);
	float	wall_projected = (25000 / ray->ray_dist);
	// printf("wall projection %f\n", wall_projected);
	// if (wall_projected > info->player->middle_of_screen)
	// 	wall_projected = info->player->middle_of_screen;
	// int	color;
	
	// int x = wall_projected / info->side1.height;
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
