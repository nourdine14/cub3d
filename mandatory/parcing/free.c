/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakebli <nakebli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 07:57:12 by nakebli           #+#    #+#             */
/*   Updated: 2023/07/23 01:51:40 by nakebli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parcing.h"

void	free_info(t_info *info)
{
	free(info->no);
	free(info->so);
	free(info->ea);
	free(info->we);
	free(info->f);
	free(info->c);
	free(info);
}

void	print_errors(char *str)
{
	printf("%s\n", str);
	exit(1);
}