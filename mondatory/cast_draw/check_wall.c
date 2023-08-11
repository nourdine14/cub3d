/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_wall.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakebli <nakebli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 05:09:32 by oaboulgh          #+#    #+#             */
/*   Updated: 2023/08/11 13:06:48 by nakebli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	has_wall(float x, float y, t_cub *info)
{
	int	i;
	int	j;

	j = x / G_SIZE;
	i = y / G_SIZE;
	if (j > long_line(info->player->map) || \
	i > height_of_map(info->player->map) || i < 0 || j < 0)
		return (1);
	if (info->player->map[i][j] == '1')
		return (1);
	if (info->player->map[i][j] == 'D')
	{
		if (diff_of_two_points(x, y, info->player->x, info->player->y) < 100)
			return (0);
		return (1);
	}
	return (0);
}

int	has_wall2(float x, float y, t_cub *info)
{
	t_player	*p;
	int			px;
	int			py;
	int			px1;
	int			py1;

	p = info->player;
	px = (int)(x / G_SIZE);
	py = (int)(y / G_SIZE);
	px1 = (int)((x + SPACE_FROM_WALL) / G_SIZE);
	py1 = (int)((y + SPACE_FROM_WALL) / G_SIZE);
	if (p->map[py][px1] == '1' || p->map[py1][px] == '1' ||
		p->map[py1][px1] == '1' \
		|| p->map[(int)((y - SPACE_FROM_WALL) / G_SIZE)][px] == '1' || 
		p->map[(int)((y - SPACE_FROM_WALL) / \
		G_SIZE)][(int)((x - SPACE_FROM_WALL) / G_SIZE)] == '1' \
		|| p->map[py1][(int)((x - SPACE_FROM_WALL) / G_SIZE)] == '1' ||
		p->map[py][(int)((x - SPACE_FROM_WALL) / G_SIZE)] == '1' \
		|| p->map[(int)((y - SPACE_FROM_WALL) / G_SIZE)][px1] == '1')
		return (1);
	return (0);
}

int	is_door(float x, float y, t_cub *info)
{
	int	i;
	int	j;

	j = x / G_SIZE;
	i = y / G_SIZE;
	if (j > long_line(info->player->map) \
	|| i > height_of_map(info->player->map) || i < 0 || j < 0)
	{
		printf("x = %d\n", i);
		printf("y = %d\n", j);
		return (1);
	}
	if (info->player->map[i][j] == 'D')
		return (1);
	return (0);
}
