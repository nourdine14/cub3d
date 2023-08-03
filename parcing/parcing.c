/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakebli <nakebli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 14:52:30 by nakebli           #+#    #+#             */
/*   Updated: 2023/08/03 13:59:34 by nakebli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parcing.h"

void	print_map(t_cub *cub)
{
	printf("Map: (height = %d)\n", cub->info->height);
	while (cub)
	{
		printf("|%s|\n", cub->line);
		cub = cub->next;
	}
}

t_info	*init_infos(t_info **info)
{
	*info = ft_calloc(1, sizeof(t_info));
	if (*info == NULL)
		print_errors("Error1\n");
	(*info)->no = ft_calloc(sizeof(char *), 1);
	(*info)->so = ft_calloc(sizeof(char *), 1);
	(*info)->ea = ft_calloc(sizeof(char *), 1);
	(*info)->we = ft_calloc(sizeof(char *), 1);
	(*info)->px = -1;
	(*info)->py = -1;
	return (*info);
}

void	read_map(char *av, t_cub **cub)
{
	t_info	*info;
	char	*line;
	int		fd;

	init_infos(&info);
	fd = open(av, O_RDONLY);
	if (fd == -1)
		print_errors("Error2\n");
	*cub = ft_lstnew(ft_strtrim(get_next_line(fd), "\n"), info, NULL);
	if ((*cub)->line == NULL)
		print_errors("Error3\n");
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

void	print_args(t_cub *cub)
{
	int	i;

	printf("Args:\n");
	i = 0;
	while (cub->info->no[i])
		printf("%s  ", cub->info->no[i++]);
	printf("\n");
	i = 0;
	while (cub->info->so[i])
		printf("%s  ", cub->info->so[i++]);
	printf("\n");
	i = 0;
	while (cub->info->ea[i])
		printf("%s  ", cub->info->ea[i++]);
	printf("\n");
	i = 0;
	while (cub->info->we[i])
		printf("%s  ", cub->info->we[i++]);
	printf("\n");
	i = 0;
	printf("flore RGB :");
	while (i < 3)
		printf("%d  ", cub->info->f[i++]);
	printf("\n");
	i = 0;
	printf("ceiling RGB :");
	while (i < 3)
		printf("%d  ", cub->info->c[i++]);
	printf("\n");
	exit(0);
}

void	free_map(t_cub *cub)
{
	t_cub	*tmp;

	while (cub)
	{
		tmp = cub;
		cub = cub->next;
		free(tmp->line);
		free(tmp);
	}
}

void	parcing(char *av, t_cub **cub)
{
	read_map(av, cub);
	free_map(*cub);
	return ;
	// delte_empty_lines(cub);
	// check_cardinal_direction(*cub);
	// print_map(*cub);
	// print_args(*cub);
}
