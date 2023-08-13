/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_wall.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 05:09:32 by oaboulgh          #+#    #+#             */
/*   Updated: 2023/08/12 17:53:18 by oaboulgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	has_wall(float x, float y, t_cub *info)
{
	int	i;
	int	j;
	
	j = x / G_SIZE;
	i = y / G_SIZE;
	if (j > long_line(info->player->map) || i > height_of_map(info->player->map) || i < 0 || j < 0)
	{
		// printf("x = %d\n", i);
		// printf("y = %d\n", j);
		// printf("\n");
		// printf("\n");
		// printf("\n");
		// exit (1);
		// sleep(2);
		return (1);
	}
	if (info->player->map[i][j] == '1')
		return (1);
	if (info->player->map[i][j] == 'D')
	{
		return (1);
	}
	return (0);
}

int	has_wall2(float x, float y, t_cub *info)
{
	int px = (int)(x / G_SIZE);
	int py = (int)(y / G_SIZE);
	int px1 = (int)((x + SPACE_FROM_WALL) / G_SIZE);
	int py1 = (int)((y + SPACE_FROM_WALL) / G_SIZE);
	int px2 = (int)((x - SPACE_FROM_WALL) / G_SIZE);
	int py2 = (int)((y - SPACE_FROM_WALL) / G_SIZE);

	// Check if the player's corners are inside a wall
	if (info->player->map[py][px1] == '1' || info->player->map[py1][px] == '1' ||
		info->player->map[py1][px1] == '1' || info->player->map[py2][px] == '1' || 
		info->player->map[py2][px2] == '1' || info->player->map[py1][px2] == '1' ||
		info->player->map[py][px2] == '1' || info->player->map[py2][px1] == '1')
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
