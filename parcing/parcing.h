/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakebli <nakebli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 14:53:08 by nakebli           #+#    #+#             */
/*   Updated: 2023/08/08 10:25:16 by nakebli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARCING_H
# define PARCING_H

# include "./../cub.h"

char	*get_next_line(int fd);
int		ft_atoi(const char *str);
int		is_map_line(char *line);
t_info	*parcing(char *av, t_cub **cub);
t_cub	*ft_lstlast(t_cub *lst);
void	ft_lstadd_back(t_cub **lst, t_cub *new);
t_cub	*ft_lstnew(char *line, t_info *info, t_cub *prev);
char	*ft_strtrim(char const *s1, char const *set);
void	check_cardinal_direction(t_cub *cub);
char	**ft_split(char	const *s, char c);
char	*ft_strchr(const char *str, int c);
void	delte_empty_lines(t_cub **cub);
void	print_errors(char *str);
int		ft_strcmp(char *s1, char *s2);
int		towd_arr_size(char **arr);
void	print_args(t_info *info);

#endif
