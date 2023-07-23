/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_directions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakebli <nakebli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 09:47:16 by nakebli           #+#    #+#             */
/*   Updated: 2023/07/23 03:42:07 by nakebli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parcing.h"

void	delte_empty_lines(t_cub **cub)
{
	t_cub	*to_delete;
	t_cub	*tmp;
	t_cub	*prev;

	tmp = *cub;
	prev = NULL;
	while (tmp != NULL && !is_map_line(tmp->line))
	{
		if (tmp->line[0] == '\0')
		{
			if (prev == NULL)
				*cub = tmp->next;
			else
				prev->next = tmp->next;
			to_delete = tmp;
			tmp = tmp->next;
			free(to_delete->line);
			free(to_delete);
		}
		else
		{
			prev = tmp;
			tmp = tmp->next;
		}
	}
}

void	split_params_check_rep(t_cub *cub)
{
	int	i;

	i = 0;
	while (cub->line[i] && (cub->line[i] == ' ' || cub->line[i] == '\t'))
		i++;
	if (cub->line && cub->line[i] == 'N' && *cub->info->no == NULL)
		cub->info->no = ft_split(cub->line, ' ', cub->info->no);
	else if (cub->line && cub->line[i] == 'S' && *cub->info->so == NULL)
		cub->info->so = ft_split(cub->line, ' ', cub->info->so);
	else if (cub->line && cub->line[i] == 'W' && *cub->info->we == NULL)
		cub->info->we = ft_split(cub->line, ' ', cub->info->we);
	else if (cub->line && cub->line[i] == 'E' && *cub->info->ea == NULL)
		cub->info->ea = ft_split(cub->line, ' ', cub->info->ea);
	else if (cub->line && cub->line[i] == 'F' && *cub->info->f == NULL)
		cub->info->f = ft_split(cub->line, ',', cub->info->f);
	else if (cub->line && cub->line[i] == 'C' && *cub->info->c == NULL)
		cub->info->c = ft_split(cub->line, ',', cub->info->c);
	else
		print_errors("Error\nInvalid cardinal direction or flor or ceiling");
}

void	check_args_validity(t_cub *cub)
{
	if (towd_arr_size(cub->info->no) != 2 || \
		towd_arr_size(cub->info->so) != 2 || \
		towd_arr_size(cub->info->we) != 2 || \
		towd_arr_size(cub->info->ea) != 2 || \
		towd_arr_size(cub->info->f) != 4 || \
		towd_arr_size(cub->info->c) != 4)
		print_errors("Error\nInvalid texture path");
	if (ft_strcmp(cub->info->no[0], "NO") || \
		ft_strcmp(cub->info->so[0], "SO") || \
		ft_strcmp(cub->info->we[0], "WE") || \
		ft_strcmp(cub->info->ea[0], "EA") || \
		ft_strcmp(cub->info->f[0], "F") || \
		ft_strcmp(cub->info->c[0], "C"))
		print_errors("Error\nInvalid cardinal direction or flor or ceiling");
}

int	wall_surounded(t_cub *cub)
{
	int	i;

	i = 0;
	while (cub->line[i])
	{
		if (cub->line[i] == '0' && (cub->line[i + 1] == ' ' || \
			cub->line[i + 1] == '\0' || i == 0 || cub->line[i - 1] == ' ' \
			|| cub->prev->line[i] == ' ' || !cub->prev->line[i] || \
			cub->next->line[i] == ' ' || cub->next->line[i] == ' '))
			return (0);
		i++;
	}
	return (1);
}

void	check_cardinal_direction(t_cub *cub)
{
	t_cub	*tmp;

	tmp = cub;
	while (tmp != NULL && !is_map_line(tmp->line))
	{
		split_params_check_rep(tmp);
		tmp = tmp->next;
	}
	check_args_validity(cub);
	while (tmp != NULL)
	{
		if (!is_map_line(tmp->line) || !wall_surounded(tmp))
		{
			print_errors("Error : Invalid map");
		}
		tmp = tmp->next;
	}
	printf("good map\n");
}
