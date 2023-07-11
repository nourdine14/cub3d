/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakebli <nakebli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 14:52:30 by nakebli           #+#    #+#             */
/*   Updated: 2023/07/11 11:29:49 by nakebli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parcing.h"

void	print_map(t_cub *cub)
{
	while (cub != NULL)
	{
		printf("%s", cub->line);
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
	*cub = ft_lstnew(get_next_line(fd), info);
	if ((*cub)->line == NULL)
		print_errors("Error3\n");
	i = 0;
	while (1)
	{
		i++ ;
		line = get_next_line(fd);
		if (!line || line[0] == '\0')
			break ;
		ft_lstadd_back(cub, ft_lstnew(line, info));
	}
	info->height = i;
	close(fd);
}

void	parcing(char *av, t_cub **cub)
{
	read_map(av, cub);
}
