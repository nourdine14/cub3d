/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 17:56:05 by oaboulgh          #+#    #+#             */
/*   Updated: 2023/08/10 12:45:19 by oaboulgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_var(t_var *var)
{
	var->x = 0;
	var->y = 0;
	var->x1 = 0;
	var->y1 = 0;
	var->i = 0;
	var->j = 0;
}

void	until_find_wall(t_cub *info, t_var *var, float ray_angle)
{
	float	point;
	// float	x;
	// float	y;

	point = 0;
	var->x = info->player->x - (cos(ray_angle) * point);
	var->y = info->player->y - (sin(ray_angle) * point);
	while (!has_wall(var->x, var->y, info))
	{
		var->x = info->player->x - (cos(ray_angle) * point);
		var->y = info->player->y - (sin(ray_angle) * point);
		point += 0.5;
	}
}

float	scale_angle(float angle)
{
	float	normalized;
	
	normalized = fmod(angle, 2 * M_PI);
	if (normalized < 0)
		normalized += 2 * M_PI;
	return (normalized);
}

void	draw_rays(t_cub *info)
{
	t_var	var;
	float	ray_angle;
	
	init_var(&var);
	ray_angle = info->player->rotation_angle - ((VIEW_ANGLE / 2) * DG);
	while (var.i <= NUM_OF_RAYS)
	{
		ray_angle = scale_angle(ray_angle);
		cast_rays(info, ray_angle, var.i);
		var.i++;
		ray_angle += (VIEW_ANGLE * DG / NUM_OF_RAYS);
	}
}
