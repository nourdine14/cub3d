/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_directions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakebli <nakebli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 09:47:16 by nakebli           #+#    #+#             */
/*   Updated: 2023/08/15 20:12:24 by nakebli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parcing.h"

void	split_params_check_rep(t_cubt *cub, char ***f, char ***c)
{
	int	i;

	i = 0;
	while (cub->line[i] && (cub->line[i] == ' ' || cub->line[i] == '\t'))
		i++;
	if (cub->line && cub->line[i] == 'N' && !(cub->info->no))
		cub->info->no = ft_split(cub->line, ' ');
	else if (cub->line && cub->line[i] == 'S' && !(cub->info->so))
		cub->info->so = ft_split(cub->line, ' ');
	else if (cub->line && cub->line[i] == 'W' && !(cub->info->we))
		cub->info->we = ft_split(cub->line, ' ');
	else if (cub->line && cub->line[i] == 'E' && !(cub->info->ea))
		cub->info->ea = ft_split(cub->line, ' ');
	else if (cub->line && cub->line[i] == 'F' && !*f)
		*f = ft_split(cub->line, ' ');
	else if (cub->line && cub->line[i] == 'C' && !*c)
		*c = ft_split(cub->line, ' ');
	else
		print_errors("Error : Invalid cardinal direction or flor or ceiling");
}

int	check_validity(char *str)
{
	int	i;
	int	num;

	i = 0;
	if (str[i] == ',')
		return (0);
	num = 0;
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9' && \
		(str[i + 1] == ',' || !str[i + 1]))
			num++;
		i++;
	}
	if (num != 3)
		return (0);
	return (1);
}

void	check_args_validity(t_cubt *cub, char **f, char **c)
{
	if (towd_arr_size(cub->info->no) != 2 || \
		towd_arr_size(cub->info->so) != 2 || \
		towd_arr_size(cub->info->we) != 2 || \
		towd_arr_size(cub->info->ea) != 2 || \
		towd_arr_size(f) != 2 || \
		towd_arr_size(c) != 2)
		print_errors("Error\nInvalid texture path or RGB value");
	if (ft_strcmp(cub->info->no[0], "NO") || \
		ft_strcmp(cub->info->so[0], "SO") || \
		ft_strcmp(cub->info->we[0], "WE") || \
		ft_strcmp(cub->info->ea[0], "EA") || \
		ft_strcmp(f[0], "F") || \
		ft_strcmp(c[0], "C"))
		print_errors("Error : Invalid cardinal direction or flor or ceiling");
	if (!check_validity(f[1]) || !check_validity(c[1]))
		print_errors("Error : Invalid RGB value");
}

int	wall_surounded(t_cubt *cub, int j)
{
	int	i;

	i = -1;
	while (cub->line[++i])
	{
		if ((cub->line[i] == '0' || is_player(cub->line[i])) \
			&& (cub->line[i + 1] == ' ' || cub->line[i + 1] == '\0' \
			|| i == 0 || cub->line[i - 1] == ' ' ||!cub->prev->line || \
			((int)ft_strlen(cub->prev->line) - 1) < i || !cub->next || \
			cub->prev->line[i] == ' ' || !cub->prev->line[i] || \
			cub->next->line[i] == ' ' || cub->next->line[i] == ' '))
			return (0);
		if (is_player(cub->line[i]))
		{
			if (cub->info->px == -1 && cub->info->py == -1)
			{
				cub->info->px = i;
				cub->info->py = j;
			}
			else
				print_errors("Error: double player position");
		}
		check_doors(cub, i, j);
	}
	return (1);
}

void	check_cardinal_direction(t_cubt *cub)
{
	char	**f;
	char	**c;
	t_cubt	*tmp;

	tmp = cub;
	f = NULL;
	c = NULL;
	while (tmp != NULL && !is_map_line(tmp->line))
	{
		split_params_check_rep(tmp, &f, &c);
		tmp = tmp->next;
	}
	check_args_validity(cub, f, c);
	get_color(cub, f, c);
	check_map(tmp, cub);
}
