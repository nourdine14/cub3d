/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 07:57:12 by nakebli           #+#    #+#             */
/*   Updated: 2023/08/20 20:34:56 by oaboulgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parcing.h"

void	print_errors(char *str)
{
	printf("%s\n", str);
	exit(1);
}

void	free_2d_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

int	is_player(char c)
{
	if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
		return (1);
	return (0);
}
