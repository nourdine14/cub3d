/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakebli <nakebli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 13:27:02 by nakebli           #+#    #+#             */
/*   Updated: 2022/11/15 13:26:34 by nakebli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strdup(const char *s1)
{
	char	*s2;
	int		i;

	s2 = ft_calloc((ft_strlen((char *)s1) + 1), sizeof(char));
	if (!s2)
		return (NULL);
	i = -1;
	while (s1[++i])
	{
		s2[i] = s1[i];
	}
	return (s2);
}

char	*ft_strchr(const char *str, int c)
{
	if (!str)
		return (NULL);
	while (*str)
	{
		if ((char)*str == (char)c)
			return ((char *)str);
		str++;
	}
	return (NULL);
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*p;
	size_t	tst_overflow;

	tst_overflow = count * size;
	if (tst_overflow != 0 && tst_overflow / size != count)
		return (NULL);
	p = malloc(count * size);
	if (!p)
		return (NULL);
	ft_memset(p, 0, count * size);
	return (p);
}

void	*ft_memset(void *ptr, int x, size_t n)
{
	char	*str;

	str = ptr;
	while (n--)
	{
		*str++ = (unsigned char)x;
	}
	return (ptr);
}
