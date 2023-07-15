/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakebli <nakebli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 14:53:08 by nakebli           #+#    #+#             */
/*   Updated: 2023/07/15 08:19:59 by nakebli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARCING_H
# define PARCING_H

# include "./../cub.h"

char	*get_next_line(int fd);
int		is_map_line(char *line);
void	parcing(char *av, t_cub **cub);
t_cub	*ft_lstlast(t_cub *lst);
void	ft_lstadd_back(t_cub **lst, t_cub *new);
t_cub	*ft_lstnew(char *line, t_info *info);
char	*ft_strtrim(char const *s1, char const *set);
void	check_cardinal_direction(t_cub *cub);
char	**ft_split(char	const *s, char c, char **splited);
char	*ft_strchr(const char *str, int c);
void	delte_empty_lines(t_cub **cub);
void	print_errors(char *str);

#endif
