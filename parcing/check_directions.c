/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_directions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakebli <nakebli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 09:47:16 by nakebli           #+#    #+#             */
/*   Updated: 2023/07/15 09:02:07 by nakebli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parcing.h"

void	print_errors(char *str)
{
	printf("%s\n", str);
	exit(1);
}

void	delte_empty_lines(t_cub **cub)
{
	t_cub	*tmp;
	t_cub	*prev;
	t_cub	*to_delete;

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
	if (cub->line && cub->line[0] == 'N' && *cub->info->no == NULL)
		cub->info->no = ft_split(cub->line, ' ', cub->info->no);
	else if (cub->line && cub->line[0] == 'S' && *cub->info->so == NULL)
		cub->info->so = ft_split(cub->line, ' ', cub->info->so);
	else if (cub->line && cub->line[0] == 'W' && *cub->info->we == NULL)
		cub->info->we = ft_split(cub->line, ' ', cub->info->we);
	else if (cub->line && cub->line[0] == 'E' && *cub->info->ea == NULL)
		cub->info->ea = ft_split(cub->line, ' ', cub->info->ea);
	else if (cub->line && cub->line[0] == 'F' && *cub->info->f == NULL)
		cub->info->f = ft_split(cub->line, ',', cub->info->f);
	else if (cub->line && cub->line[0] == 'C' && *cub->info->c == NULL)
		cub->info->c = ft_split(cub->line, ',', cub->info->c);
	else
	{
		printf("Error4545\n");
		exit(0);
	}
}

int	towd_arr_size(char **arr)
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
		i++;
	return (i);
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
	if (towd_arr_size(cub->info->no) != 2 || \
		towd_arr_size(cub->info->so) != 2 || \
		towd_arr_size(cub->info->we) != 2 || \
		towd_arr_size(cub->info->ea) != 2 || \
		towd_arr_size(cub->info->f) != 4 || \
		towd_arr_size(cub->info->c) != 4)
		print_errors("Error\nInvalid NO texture path");
}
