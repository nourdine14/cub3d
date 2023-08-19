/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_wall.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 05:09:32 by oaboulgh          #+#    #+#             */
/*   Updated: 2023/08/19 16:44:25 by oaboulgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

float	diff_of_two_points(float x, float y, float x1, float y1)
{
	return (sqrt((x1 - x) * (x1 - x) + (y1 - y) * (y1 - y)));
}

int	long_line2(char **map, int ix)
{
	int	i;
	int	j;
	int	x;

	i = 0;
	x = 0;
	j = 0;
	while (map[ix][j])
		j++;
	return (j);
}

int	has_wall(float x, float y, t_cub *info)
{
	int	i;
	int	j;

	j = x / G_SIZE;
	i = y / G_SIZE;

	if (j > long_line2(info->player->map, i) || i > \
	height_of_map(info->player->map) || i < 0 || j < 0)
	{
		return (1);
	}
	if (info->player->map[i][j] == '1')
		return (1);
	if (info->player->map[i][j] == 'D')
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

	j = x / G_SIZE;
	i = y / G_SIZE;
	if (info->player->map[i][j] == 'D' || info->player->map[i][j] == 'C')
		return (1);
	j = (x + 1) / G_SIZE;
	i = (y + 1) / G_SIZE;
	if (info->player->map[i][j] == 'D' || info->player->map[i][j] == 'C')
		return (1);
	j = (x - 1) / G_SIZE;
	i = (y - 1) / G_SIZE;
	if (info->player->map[i][j] == 'D' || info->player->map[i][j] == 'C')
		return (1);
	return (0);
}
