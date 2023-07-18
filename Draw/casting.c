/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   casting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 04:52:06 by oaboulgh          #+#    #+#             */
/*   Updated: 2023/07/18 17:58:05 by oaboulgh         ###   ########.fr       */
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

float	diff_of_two_points(float x, float y, float x1, float y1)
{
	return (sqrt((x1 - x) * (x1 - x) + (y1 - y) * (y1 - y)));
}

void	cast_rays(t_cub *info, float ray_angle)
{
	float	xstep;
	float	ystep;
	float	xintersection;
	float	yintersection;
	float	xherizontalle_hit_wall;
	float	yherizontalle_hit_wall;

	//*Horizontale*//

	yintersection = (floor(info->player->y / G_SIZE) * G_SIZE);
	if (!ray_lookig_up(ray_angle))
		yintersection += G_SIZE;
	xintersection = info->player->x + (yintersection - info->player->y)/ tan(ray_angle);
	
	
	ystep = G_SIZE;
	xstep = G_SIZE / tan(ray_angle);

	if (ray_lookig_up(ray_angle))
		ystep *= -1;
	if (ray_lookig_up(ray_angle))
		xstep *= -1;
	float	IX = xintersection;
	float	IY = yintersection;
	bool	b = false;
	if (ray_lookig_up(ray_angle))
		IY--;
	while (IX >= 0 && IX <= COL * G_SIZE && IY >= 0 && IY <= ROW * G_SIZE)
	{
		if (has_wall(IX, IY, info))
		{
			b = true;
			xherizontalle_hit_wall = IX;
			yherizontalle_hit_wall = IY;
			// dda(info->player->x, info->player->y, IX, IY, info, 0xff0000);
			break;
		}
		else
		{
			IX += xstep;
			IY += ystep;
		}
	}
	
	//*Verticale*//
	float	xvertical_hit_wall;
	float	yvertical_hit_wall;

	xintersection = (floor(info->player->x / G_SIZE) * G_SIZE);
	if (!ray_lookig_left(ray_angle))
		xintersection += G_SIZE;
	yintersection = info->player->y + (xintersection - info->player->x) * tan(ray_angle);
	
	
	xstep = G_SIZE;
	ystep = G_SIZE * tan(ray_angle);

	if (ray_lookig_left(ray_angle))
		ystep *= -1;
	if (ray_lookig_left(ray_angle))
		xstep *= -1;
	IX = xintersection;
	IY = yintersection;
	bool	a = false;
	if (ray_lookig_left(ray_angle))
		IX--;
	while (IX >= 0 && IX <= COL * G_SIZE && IY >= 0 && IY <= ROW * G_SIZE)
	{
		if (has_wall(IX, IY, info))
		{
			a = true;
			xvertical_hit_wall = IX;
			yvertical_hit_wall = IY;
			// dda(info->player->x, info->player->y, IX, IY, info, 0x0073e6);
			break;
		}
		else
		{
			IX += xstep;
			IY += ystep;
		}
	}
	float xhit;
	float yhit;
	if (b)
		xhit = diff_of_two_points(info->player->x, info->player->y, \
			xherizontalle_hit_wall, yherizontalle_hit_wall);
	else
		xhit = MAXFLOAT;
	if (a)
		yhit = diff_of_two_points(info->player->x, info->player->y, \
			xvertical_hit_wall, yvertical_hit_wall);
	else
		yhit = MAXFLOAT;
	if (xhit <= yhit)
	{
		IX = xherizontalle_hit_wall;
		IY = yherizontalle_hit_wall;
	}
	else
	{
		IX = xvertical_hit_wall;
		IY = yvertical_hit_wall;
	}
	dda(info->player->x, info->player->y, IX, IY, info, 0xff0000);
}
