/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 14:20:13 by oaboulgh          #+#    #+#             */
/*   Updated: 2023/08/09 17:56:11 by oaboulgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	full_player_info(t_player *player, char c, int i, int j)
{
	player->x = (i * G_SIZE) + MOVE_SPEED * cos(player->rotation_angle) + G_SIZE / 2;
	player->y = (j * G_SIZE) + MOVE_SPEED * sin(player->rotation_angle) + G_SIZE / 2;
	// player->mini_map_x = (i * G_SIZE * MINI_MAP_SCALE) + MOVE_SPEED * cos(player->rotation_angle) + G_SIZE * MINI_MAP_SCALE / 2;
	
	// player->mini_map_y = (j * G_SIZE * MINI_MAP_SCALE) + MOVE_SPEED * sin(player->rotation_angle) + G_SIZE * MINI_MAP_SCALE / 2;
	
	player->mouse_x = player->x;
	player->mouse_y = player->y;
	if (c == 'N')
	{
		player->rotation_angle = -M_PI_2;
		player->turn_d = 1;
		player->walk_d = 1;
	}
	if (c == 'E')
	{
		player->rotation_angle = -M_PI;
		player->turn_d = 1;
		player->walk_d = 1;
	}
	if (c == 'W')
	{
		player->rotation_angle = M_PI;
		player->turn_d = -1;
		player->walk_d = -1;
	}
	if (c == 'S')
	{
		player->rotation_angle = M_PI_2;
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
				full_player_info(player, map[i][j], j, i);
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
	player->middle_of_screen = (G_SIZE * ROW) / 2;
	get_x_y_position(player, map);
	player->radius = 5;
	player->turn_d = 1;
	player->walk_d = 1;
	player->rotate_left = 0;
	player->rotate_right = 0;
	player->move_forward = 0;
	player->move_backward = 0;
	player->move_forward_l = 0;
	player->move_forward_r = 0;
	player->move_speed = 1;
	player->rotation_speed = 2 * (M_PI / 180);
	player->shot = 0;
	player->stop = 0;
	player->hp = 150;
}

void	draw_player(t_cub *info, t_player *player)
{
	float	x1;
	float	y1;

	x1 = 100 + (cos(info->player->rotation_angle) * 30);
	y1 =  100 + (sin(info->player->rotation_angle) * 30);
	draw_circle(info, player);
	dda(100, 100, \
	x1, y1, info, 0x008000);
}

void	draw_circle(t_cub *info, t_player *player)
{
	int	a;
	int	b;
	int	n;

	n = (2 * player->radius) + 1;
	a = 100;
	b = 100;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			a = i - player->radius;
			b = j - player->radius;
			if ((a * a) + (b * b) <= player->radius * player->radius + 1)
			{
				if ((a + 100) >= 0 && (b + 100) >= 0 && (b + 100) <= ROW * G_SIZE \
					&& (a + 100) <= COL * G_SIZE)
				my_mlx_pixel_put(&info->img,  (a + 100), \
					(b + 100), 0xcc6600);
			}
		}
	}
}
