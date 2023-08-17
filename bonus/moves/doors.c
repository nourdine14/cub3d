/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakebli <nakebli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 14:56:10 by oaboulgh          #+#    #+#             */
/*   Updated: 2023/08/17 23:50:59 by nakebli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	continue_full(t_cub *info, int num_of_doors, char **map)
{
	int	i;
	int	j;

	num_of_doors *= 2;
	info->num_of_doors = num_of_doors;
	info->doors_pos = malloc(sizeof(int) * (num_of_doors));
	i = 0;
	num_of_doors = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j] != '\0')
		{
			if (map[i][j] == 'D')
			{
				info->doors_pos[num_of_doors++] = j;
				info->doors_pos[num_of_doors++] = i;
			}
			j++;
		}
		i++;
	}
}

void	init_doors_pos(t_cub *info, char **map)
{
	int	i;
	int	j;
	int	num_of_doors;

	i = 0;
	num_of_doors = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j] != '\0')
		{
			if (map[i][j] == 'D')
				num_of_doors++;
			j++;
		}
		i++;
	}
	if (num_of_doors == 0)
	{
		info->doors_pos = NULL;
		return ;
	}
	continue_full(info, num_of_doors, map);
}

void	check_doors_distance_from_player(t_cub *info)
{
	int	i;
	int	x;
	int	y;

	i = 0;
	if (!info->doors_pos)
		return ;
	while (i < info->num_of_doors)
	{
		if ((diff_of_two_points(info->player->x - 25, \
			info->player->y - 25, info->doors_pos[i] * G_SIZE, \
			info->doors_pos[i + 1] * G_SIZE) < 100) && info->player->open)
			info->player->map[info->doors_pos[i + 1]][info->doors_pos[i]] = 'C';
		else if ((diff_of_two_points(info->player->x - 25, \
		info->player->y - 25, info->doors_pos[i] * G_SIZE, \
			info->doors_pos[i + 1] * G_SIZE) <= 100) \
			&& !info->player->open && (diff_of_two_points(info->player->x - 25, \
			info->player->y - 25, info->doors_pos[i] * G_SIZE, \
			info->doors_pos[i + 1] * G_SIZE) > 80))
		{
			x = info->doors_pos[i];
			y = info->doors_pos[i + 1];
			info->player->map[y][x] = 'D';
		}
		i += 2;
	}
}
