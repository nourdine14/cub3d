/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 14:52:30 by nakebli           #+#    #+#             */
/*   Updated: 2023/08/19 20:19:07 by oaboulgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parcing.h"

t_info	*init_infos(t_info **info)
{
	*info = ft_calloc(1, sizeof(t_info));
	if (*info == NULL)
		print_errors("Error1\n");
	(*info)->no = NULL;
	(*info)->so = NULL;
	(*info)->ea = NULL;
	(*info)->we = NULL;
	(*info)->px = -1;
	(*info)->py = -1;
	return (*info);
}

void	read_map(char *av, t_cubt **cub)
{
	t_info	*info;
	char	*line;
	int		fd;

	init_infos(&info);
	fd = open(av, O_RDONLY);
	if (fd == -1)
		print_errors("Error\ncan't open file");
	*cub = ft_lstnew(ft_strtrim(get_next_line(fd), "\n"), info, NULL);
	if (!(*cub) || (*cub)->line == NULL)
		print_errors("Error\n");
	info->height = 0;
	while (1)
	{
		info->height++ ;
		line = ft_strtrim(get_next_line(fd), "\n");
		if (!line)
			break ;
		ft_lstadd_back(cub, ft_lstnew(line, info, ft_lstlast(*cub)));
	}
	close(fd);
}

void	free_map(t_cubt *cub)
{
	t_cubt	*tmp;

	while (cub)
	{
		tmp = cub;
		cub = cub->next;
		free(tmp->line);
		free(tmp);
	}
}

t_info	*get_info_map(t_cubt *cub)
{
	t_info	*info;
	t_cubt	*tmp;
	int		i;

	i = 0;
	info = cub->info;
	info->map = ft_calloc(info->height + 1, sizeof(char *));
	while (cub && !is_map_line(cub->line))
	{
		free (cub->line);
		tmp = cub;
		cub = cub->next;
		free(tmp);
	}
	while (cub)
	{
		info->map[i] = ft_strdup(cub->line);
		free(cub->line);
		i++;
		tmp = cub;
		cub = cub->next;
		free(tmp);
	}
	info->map[i] = NULL;
	return (info);
}

t_info	*parcing(char *av, t_cubt **cub)
{
	t_info	*info;

	info = NULL;
	read_map(av, cub);
	delte_empty_lines(cub);
	check_cardinal_direction(*cub);
	info = get_info_map(*cub);
	return (info);
}
