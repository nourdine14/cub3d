/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakebli <nakebli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 14:52:30 by nakebli           #+#    #+#             */
/*   Updated: 2023/07/14 09:19:02 by nakebli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parcing.h"

void	print_map(t_cub *cub)
{
	printf("Map:\n");
	while (cub)
	{
		printf("%s\n", cub->line);
		cub = cub->next;
	}
}

void	print_errors(char *str)
{
	printf("%s\n", str);
	exit(1);
}

void	read_map(char *av, t_cub **cub)
{
	t_info	*info;
	char	*line;
	int		i;
	int		fd;

	info = malloc(sizeof(t_info));
	if (info == NULL)
		print_errors("Error1\n");
	fd = open(av, O_RDONLY);
	if (fd == -1)
		print_errors("Error2\n");
	*cub = ft_lstnew(ft_strtrim(get_next_line(fd), "\n"), info);
	if ((*cub)->line == NULL)
		print_errors("Error3\n");
	i = 0;
	while (1)
	{
		i++ ;
		line = ft_strtrim(get_next_line(fd), "\n");
		if (!line)
			break ;
		ft_lstadd_back(cub, ft_lstnew(line, info));
	}
	info->height = i;
	close(fd);
}

void	delte_empty_lines(t_cub **cub)
{
	t_cub	*tmp;
	t_cub	*prev;
	t_cub	*to_delete;

	tmp = *cub;
	prev = NULL;
	while (tmp != NULL)
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

void	parcing(char *av, t_cub **cub)
{
	read_map(av, cub);
	print_map(*cub);
	delte_empty_lines(cub);
	print_map(*cub);
}
