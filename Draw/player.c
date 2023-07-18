/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 14:20:13 by oaboulgh          #+#    #+#             */
/*   Updated: 2023/07/18 04:30:44 by oaboulgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	full_player_info(t_player *player, char c, int i, int j)
{
	player->x = (i * G_SIZE) + MOVE_SPEED * cos(player->rotation_angle) + G_SIZE / 2;
	player->y = (j * G_SIZE) + MOVE_SPEED * sin(player->rotation_angle) + G_SIZE / 2;
	if (c == 'N')
	{
		player->turn_d = 1;
		player->walk_d = 1;
	}
	if (c == 'E')
	{
		player->turn_d = 1;
		player->walk_d = 1;
	}
	if (c == 'W')
	{
		player->turn_d = -1;
		player->walk_d = -1;
	}
	if (c == 'S')
	{
		player->turn_d = -1;
		player->walk_d = -1;
	}
}

void	get_x_y_position(t_player *player, char **map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < ROW)
	{
		j = 0;
		while (j < COL)
		{
			if (map[i][j] == 'N' || map[i][j] == 'W' || map[i][j] == 'E' \
				|| map[i][j] == 'S')
			{
				full_player_info(player, map[i][j], i, j);
				return ;
			}
			j++;
		}
		i++;
	}
}

void	init_player(t_player *player, char **map)
{
	player->map = map;
	get_x_y_position(player, map);
	player->radius = 5;
	player->turn_d = 1;
	player->walk_d = 1;
	player->rotate_left = 0;
	player->rotate_right = 0;
	player->move_forward = 0;
	player->move_backward = 0;
	player->rotation_angle = M_PI/6;
	player->move_speed = 1;
	player->rotation_speed = 2 * (M_PI / 180);
}

void	draw_player(t_cub *info, t_player *player)
{
	int		a;
	int		x1;
	int		y1;

	x1 = player->x + (cos(info->player->rotation_angle) * 30);
	y1 =  player->y + (sin(info->player->rotation_angle) * 30);
	draw_circle(info, player);
	dda(player->x,  player->y, x1, y1, info, 0x008000);
}

void	draw_circle(t_cub *info, t_player *player)
{
	int	a;
	int	b;
	int	n;

	n = (2 * player->radius) + 1;
	a = player->x;
	b = player->y;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			a = i - player->radius;
			b = j - player->radius;
			if ((a * a) + (b * b) <= player->radius * player->radius + 1)
				my_mlx_pixel_put(info, a + player->x, \
					b + player->y, 0xcc6600);
		}
	}
}
