/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_wall.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 05:09:32 by oaboulgh          #+#    #+#             */
/*   Updated: 2023/08/20 20:01:03 by oaboulgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	has_wall(float x, float y, t_cub *info)
{
	int	i;
	int	j;

	j = x / G_SIZE;
	i = y / G_SIZE;
	if (j > long_line2(info->player->map, i) || i > \
	height_of_map(info->player->map) || i < 0 || j < 0)
		return (1);
	if (info->player->map[i][j] == '1')
		return (1);
	if (info->player->map[i][j] == 'D')
		return (1);
	return (0);
}

int	has_wall_only(float x, float y, t_cub *info)
{
	int	i;
	int	j;

	j = x / G_SIZE;
	i = y / G_SIZE;
	if (j > long_line2(info->player->map, i) || i > \
	height_of_map(info->player->map) || i < 0 || j < 0)
		return (1);
	if (info->player->map[i][j] == '1')
		return (1);
	return (0);
}

int	is_wall(t_player *p, char c, float x, float y)
{
	int			px;
	int			py;
	int			px1;
	int			py1;

	px = (int)(x / G_SIZE);
	py = (int)(y / G_SIZE);
	px1 = (int)((x + SPACE_FROM_WALL) / G_SIZE);
	py1 = (int)((y + SPACE_FROM_WALL) / G_SIZE);
	if (p->map[py][px1] == c || p->map[py1][px] == c ||
		p->map[py1][px1] == c \
		|| p->map[(int)((y - SPACE_FROM_WALL) / G_SIZE)][px] == c || 
		p->map[(int)((y - SPACE_FROM_WALL) / \
		G_SIZE)][(int)((x - SPACE_FROM_WALL) / G_SIZE)] == c \
		|| p->map[py1][(int)((x - SPACE_FROM_WALL) / G_SIZE)] == c ||
		p->map[py][(int)((x - SPACE_FROM_WALL) / G_SIZE)] == c \
		|| p->map[(int)((y - SPACE_FROM_WALL) / G_SIZE)][px1] == c)
		return (1);
	return (0);
}

int	has_wall2(float x, float y, t_cub *info)
{
	if (is_wall(info->player, '1', x, y) || is_wall(info->player, 'D', x, y))
		return (1);
	return (0);
}

int	is_door(float x, float y, t_cub *info)
{
	int	i;
	int	j;

	i = y / G_SIZE;
	j = (x + 1) / G_SIZE;
	if (info->player->map[i][j] == 'D' || info->player->map[i][j] == 'C')
		return (1);
	i = (y + 1) / G_SIZE;
	j = x / G_SIZE;
	if (info->player->map[i][j] == 'D' || info->player->map[i][j] == 'C')
		return (1);
	i = (y - 1) / G_SIZE;
	j = x / G_SIZE;
	if (info->player->map[i][j] == 'D' || info->player->map[i][j] == 'C')
		return (1);
	i = y / G_SIZE;
	j = (x - 1) / G_SIZE;
	if (info->player->map[i][j] == 'D' || info->player->map[i][j] == 'C')
		return (1);
	return (0);
}
