/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakebli <nakebli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 14:52:30 by nakebli           #+#    #+#             */
/*   Updated: 2023/07/23 00:57:29 by nakebli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parcing.h"

void	print_map(t_cub *cub)
{
	printf("Map: (height = %d)\n", cub->info->height);
	while (cub)
	{
		printf("%s\n", cub->line);
		cub = cub->next;
	}
	exit(1);
}

t_info	*init_infos(t_info **info)
{
	*info = ft_calloc(1, sizeof(t_info));
	if (*info == NULL)
		print_errors("Error1\n");
	(*info)->no = ft_calloc(2, sizeof(char *));
	(*info)->so = ft_calloc(2, sizeof(char *));
	(*info)->ea = ft_calloc(2, sizeof(char *));
	(*info)->we = ft_calloc(2, sizeof(char *));
	(*info)->f = ft_calloc(2, sizeof(char *));
	(*info)->c = ft_calloc(2, sizeof(char *));
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

int	is_map_line(char *line)
{
	int	i;

	i = 0;
	if (!line[0])
		return (0);
	while (line[i])
	{
		if (line[i] != '1' && line[i] != '0' && \
		line[i] != ' ' && line[i] != '\t' && \
		line[i] != 'N' && line[i] != 'S' && \
		line[i] != 'W' && line[i] != 'E')
			return (0);
		i++;
	}
	return (1);
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
	while (cub->info->f[i])
		printf("%s  ", cub->info->f[i++]);
	printf("\n");
	i = 0;
	while (cub->info->c[i])
		printf("%s  ", cub->info->c[i++]);
	printf("\n");
}

void	parcing(char *av, t_cub **cub)
{
	read_map(av, cub);
	delte_empty_lines(cub);
	check_cardinal_direction(*cub);
	print_map(*cub);
	print_args(*cub);
}
