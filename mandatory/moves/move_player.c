/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 18:06:23 by nakebli           #+#    #+#             */
/*   Updated: 2023/08/20 20:42:40 by oaboulgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	move_player2(t_cub *info, float dx, float dy)
{
	if (info->player->move_forward_l)
		info->player->x += dy;
	if (info->player->move_forward_l)
		info->player->y -= dx;
	if (info->player->move_forward_r)
		info->player->x -= dy;
	if (info->player->move_forward_r)
		info->player->y += dx;
	if (info->player->move_forward)
		info->player->x += dx;
	if (info->player->move_forward)
		info->player->y += dy;
	if (info->player->move_backward)
		info->player->x -= dx;
	if (info->player->move_backward)
		info->player->y -= dy;
}

void	move_player(t_player *player, t_cub *info)
{
	float		angle;
	float		dx;
	float		dy;

	angle = player->rotation_angle;
	angle = scale_angle(angle);
	dx = cos(angle) * MOVE_SPEED;
	dy = sin(angle) * MOVE_SPEED;
	move_player2(info, dx, dy);
	if (player->rotate_left)
		player->rotation_angle -= ROTATION_SPEED;
	if (player->rotate_right)
		player->rotation_angle += ROTATION_SPEED;
}

int	handle_mouse_move(int x, int y, t_cub *info)
{
	int	dx;
	int	dy;

	dx = x - info->player->mouse_x;
	dy = y - info->player->mouse_y;
	info->player->mouse_x = x;
	info->player->mouse_y = y;
	if (x < 1500 && y < 1500 && x > 0 && y > 0)
		info->player->rotation_angle += 0.005 * dx;
	if (x < 1500 && y < 1500 && x > 0 && y > 0 && \
		dy > 0 && info->player->middle_of_screen > 100)
		info->player->middle_of_screen -= 2;
	if (x < 1500 && y < 1500 && x > 0 && y > 0 && \
		dy < 0 && info->player->middle_of_screen < (1500 - 100))
		info->player->middle_of_screen += 2;
	return (0);
}

int	long_line(char **map)
{
	int	i;
	int	j;
	int	x;

	i = 0;
	x = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
			j++;
		if (j > x)
			x = j;
		i++;
	}
	return (x);
}

int	height_of_map(char **map)
{
	int	i;

	i = 0;
	while (map[i])
		i++;
	return (i);
}
