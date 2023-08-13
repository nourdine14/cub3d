/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakebli <nakebli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 12:55:21 by nakebli           #+#    #+#             */
/*   Updated: 2023/07/10 15:50:09 by nakebli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

char	*get_next_line(int fd);
char	*ft_strdup(const char *s1);
char	*ft_strchr(const char *str, int c);
size_t	ft_strlen(const char *str);
void	*ft_calloc(size_t count, size_t size);
void	*ft_memset(void *ptr, int x, size_t n);

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100
# endif

#endif