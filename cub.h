/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakebli <nakebli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 13:08:55 by nakebli           #+#    #+#             */
/*   Updated: 2023/07/10 16:50:19 by nakebli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <mlx.h>

# include "get_next_line/get_next_line.h"

typedef struct s_cub
{
	void					*mlx;
	void					*win;
	char					*line;
	struct s_info			*info;
	struct s_cub			*next;
}	t_cub;

typedef struct s_info
{
	int		height;
}	t_info;

void	parcing(char *av, t_cub **cub);
char	*get_next_line(int fd);

#endif
