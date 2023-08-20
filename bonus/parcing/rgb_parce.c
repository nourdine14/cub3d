/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb_parce.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 22:31:56 by nakebli           #+#    #+#             */
/*   Updated: 2023/08/20 13:53:44 by oaboulgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parcing.h"

static void	check_splitted_args(char **f, char **c, char **floor, char **ceil)
{
	free_2d_arr(f);
	if (!floor)
		print_errors("Error\nInvalid flor color");
	free_2d_arr(c);
	if (!ceil)
		print_errors("Error\nInvalid ceiling color");
}

static void	color_value(char **item, t_cubt *cub, char flag)
{
	int	i;

	i = 0;
	if (flag == 'f')
	{
		while (item[i])
		{
			cub->info->f[i] = ft_atoi(item[i]);
			if (cub->info->f[i] < 0 || cub->info->f[i] > 255)
				print_errors("Error\nInvalid color");
			i++;
		}
	}
	else if (flag == 'c')
	{
		while (item[i])
		{
			cub->info->c[i] = ft_atoi(item[i]);
			if (cub->info->c[i] < 0 || cub->info->c[i] > 255)
				print_errors("Error\nInvalid color");
			i++;
		}
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
	color_value(floor, cub, 'f');
	free_2d_arr(floor);
	color_value(ceiling, cub, 'c');
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
			print_errors("Error\nInvalid map");
		}
		tmp = tmp->next;
	}
	if (cub->info->px == -1 && cub->info->py == -1)
		print_errors("Error\nno player position seted");
}

int	check_name(char *str)
{
	int		i;
	int		j;
	char	test[5];

	i = 0;
	test[0] = '.';
	test[1] = 'c';
	test[2] = 'u';
	test[3] = 'b';
	test[4] = '\0';
	while (str[i])
		i++;
	if (i <= 4)
		return (0);
	j = i - 4;
	i = 0;
	while (str[j])
	{
		if (str[j] != test[i])
			return (0);
		j++;
		i++;
	}
	return (1);
}
