/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb_parce.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakebli <nakebli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 22:31:56 by nakebli           #+#    #+#             */
/*   Updated: 2023/08/09 23:17:39 by nakebli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parcing.h"

static void	check_splitted_args(char **f, char **c, char **floor, char **ceil)
{
	free_2d_arr(f);
	if (!floor)
		print_errors("Error : Invalid flor color");
	free_2d_arr(c);
	if (!ceil)
		print_errors("Error : Invalid ceiling color");
}

static void	color_value(char **item, t_cubt *cub)
{
	int	i;

	i = 0;
	while (item[i])
	{
		cub->info->f[i] = ft_atoi(item[i]);
		if (cub->info->f[i] < 0 || cub->info->f[i] > 255)
			print_errors("Error : Invalid color");
		i++;
	}
}

void	get_color(t_cubt *cub, char **f, char **c)
{
	char	**floor;
	char	**ceiling;

	floor = NULL;
	ceiling = NULL;
	floor = ft_split(f[1], ',');
	ceiling = ft_split(c[1], ',');
	check_splitted_args(f, c, floor, ceiling);
	color_value(floor, cub);
	free_2d_arr(floor);
	color_value(ceiling, cub);
	free_2d_arr(ceiling);
}

void	check_map(t_cubt *tmp, t_cubt *cub)
{
	int	i;

	i = 0;
	while (tmp != NULL)
	{
		i++;
		if (!is_map_line(tmp->line) || !wall_surounded(tmp, i++))
		{
			print_errors("Error : Invalid map");
		}
		tmp = tmp->next;
	}
	if (cub->info->px == -1 && cub->info->py == -1)
		print_errors("Error: no player position seted");
}
