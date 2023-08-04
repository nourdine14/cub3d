/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 05:14:00 by oaboulgh          #+#    #+#             */
/*   Updated: 2023/08/04 05:43:36 by oaboulgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void move_player(t_player *player, t_cub *info)
{
    float	x;
    float	y;
    float	angle;
	// float	dif1;
	// float	dif2;
	// t_ray	ray;

    angle = player->rotation_angle;
    x = player->x;
    y = player->y;
    angle = scale_angle(angle);
    // Move the player in the x and y directions separately
    float dx = cos(angle) * MOVE_SPEED;
    float dy = sin(angle) * MOVE_SPEED;

    // Check for collisions in the x direction
    if (player->move_forward && !has_wall2(x + dx, y, info))
        x += dx;
    if (player->move_backward && !has_wall2(x - dx, y, info))
        x -= dx;

    // Check for collisions in the y direction
    if (player->move_forward && !has_wall2(x, y + dy, info))
        y += dy;
    if (player->move_backward && !has_wall2(x, y - dy, info))
        y -= dy;

    // Update the player's position
    player->x = x;
    player->y = y;

    // Update the rotation angle
    if (player->rotate_left)
        player->rotation_angle -= player->rotation_speed;
    if (player->rotate_right)
        player->rotation_angle += player->rotation_speed;
}
