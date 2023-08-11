/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_empty_lines.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakebli <nakebli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 05:08:08 by nakebli           #+#    #+#             */
/*   Updated: 2023/08/09 23:19:01 by nakebli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parcing.h"

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

static int	is_empty_line(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] != ' ' && s[i] != '\t')
			return (0);
		i++;
	}
	return (1);
}

void	delete_prefixes_empty_lines(t_cubt **cub, t_cubt *tmp)
{
	t_cubt	*to_delete;
	t_cubt	*prev;

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
	if (tmp == NULL)
		print_errors("Error : No map");
}

void	delte_empty_lines(t_cubt **cub)
{
	t_cubt	*to_delete;
	t_cubt	*tmp;

	tmp = *cub;
	delete_prefixes_empty_lines(cub, tmp);
	tmp = ft_lstlast(*cub);
	while (tmp && is_empty_line(tmp->line))
	{
		to_delete = tmp;
		tmp = tmp->prev;
		tmp->next = NULL;
		free(to_delete->line);
		free(to_delete);
	}
}

int	is_player(char c)
{
	if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
		return (1);
	return (0);
}
