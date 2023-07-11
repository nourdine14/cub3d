/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakebli <nakebli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 14:53:08 by nakebli           #+#    #+#             */
/*   Updated: 2023/07/10 16:49:30 by nakebli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARCING_H
# define PARCING_H

# include "./../cub.h"

char	*get_next_line(int fd);
void	parcing(char *av, t_cub **cub);
t_cub	*ft_lstlast(t_cub *lst);
void	ft_lstadd_back(t_cub **lst, t_cub *new);
t_cub	*ft_lstnew(char *line, t_info *info);

#endif
