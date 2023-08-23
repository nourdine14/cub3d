/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calcul_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 13:29:33 by oaboulgh          #+#    #+#             */
/*   Updated: 2023/08/20 13:34:11 by oaboulgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	long_line2(char **map, int i)
{
	int	j;

	j = 0;
	while (map[i][j])
		j++;
	return (j);
}

int	height_of_map(char **map)
{
	int	i;

	i = 0;
	while (map[i])
		i++;
	return (i);
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

bool	ray_lookig_up(double angle)
{
	if (angle < M_PI && angle > 0)
		return (false);
	return (true);
}

bool	ray_lookig_left(double angle)
{
	if (angle < M_PI_2 || angle > 3 * M_PI_2)
		return (false);
	return (true);
}
