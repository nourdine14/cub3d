/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 14:20:13 by oaboulgh          #+#    #+#             */
/*   Updated: 2023/07/11 21:01:19 by oaboulgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	full_player_info(t_palyer *player, char c, int i, int j)
{
	player->x = i * G_SIZE;
	player->y = j * G_SIZE;
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

void	get_x_y_position(t_palyer *player, char **map)
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

void	init_player(t_palyer *player, char **map)
{
	player->map = map;
	get_x_y_position(player, map);
	player->radius = 5;
	player->turn_d = 1;
	player->walk_d = 1;
	player->rotation_angle = M_PI_2;
	player->move_speed = 1;
	player->rotation_speed = 3 * (M_PI / 180);
}
