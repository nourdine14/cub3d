/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakebli <nakebli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 13:24:49 by nakebli           #+#    #+#             */
/*   Updated: 2023/07/11 13:28:12 by nakebli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parcing.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size > 0)
	{
		while (i < size - 1)
		{
			if (src[i] == '\0')
				break ;
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (ft_strlen((char *)src));
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		j;
	char	*s;

	i = 0;
	if (!s1)
		return (NULL);
	if (!set)
		return (ft_strdup(s1));
	j = ft_strlen((char *)s1) - 1;
	while (ft_strchr(set, s1[i]) && s1[i])
		i++;
	while (ft_strchr(set, s1[j]) && j > 0)
		j--;
	if (i > j)
		return (ft_strdup(""));
	s = malloc(j - i + 2);
	if (!s)
		return (NULL);
	ft_strlcpy(s, (char *)s1 + i, j - i + 2);
    free((char *)s1);
	return (s);
}
