/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakebli <nakebli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 13:08:55 by nakebli           #+#    #+#             */
/*   Updated: 2023/07/14 10:00:08 by nakebli          ###   ########.fr       */
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
	char	**no;
	char	**so;
	char	**ea;
	char	**we;
	char	**f;
	char	**c;
	int		height;
}	t_info;

void	parcing(char *av, t_cub **cub);
char	*get_next_line(int fd);
void	print_map(t_cub *cub);

#endif
