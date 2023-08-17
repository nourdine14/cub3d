/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakebli <nakebli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 12:48:25 by nakebli           #+#    #+#             */
/*   Updated: 2022/11/15 16:55:18 by nakebli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	tlen;
	char	*js;
	int		i;
	int		j;

	tlen = 0;
	if (!s1)
		return (ft_strdup(s2));
	if (*s2 == 0)
		return (free((char *)s1), (char *)s1);
	tlen = ft_strlen((char *)s1) + ft_strlen((char *)s2) + 1;
	js = ft_calloc((int)tlen, sizeof(char));
	if (!js)
		return (0);
	i = 0;
	j = 0;
	while (s1[j] != '\0')
		js[i++] = s1[j++];
	j = 0;
	while (s2[j] != '\0')
		js[i++] = s2[j++];
	free ((void *)s1);
	return (js);
}

static char	*befor_nl(char *save)
{
	char	*s;
	int		i;

	i = 0;
	if (*save == 0)
	{
		free(save);
		return (NULL);
	}
	while (save[i] && save[i] != '\n')
		i++;
	s = ft_calloc(i + 2, sizeof(char));
	if (!s)
		return (free(save), NULL);
	i = 0;
	while (save[i] && save[i] != '\n')
	{
		s[i] = save[i];
		i++;
	}
	s[i] = save[i];
	return ((char *)s);
}

static char	*after_nl(char *save)
{
	char	*s;
	int		i;
	int		j;

	i = 0;
	while (save[i] && save[i] != '\n')
		i++;
	if (!save[i])
		return (s = ft_calloc(1, 1), free(save), s);
	i++;
	s = ft_calloc((ft_strlen(save) - i) + 2, sizeof(char));
	if (!s)
		return (free(save), NULL);
	j = -1;
	while (save[i])
	{
		s[++j] = save[i];
		i++;
	}
	return (free(save), (char *)s);
}

static char	*read_and_save(char *save, int fd)
{
	char	*buffer;
	int		read_ret;

	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buffer)
		return (NULL);
	read_ret = 1;
	while (read_ret != 0 && !ft_strchr(save, '\n'))
	{
		read_ret = read(fd, buffer, BUFFER_SIZE);
		if (read_ret == -1)
		{
			if (save)
				free (save);
			free(buffer);
			return (NULL);
		}
		buffer[read_ret] = 0;
		if (read_ret == 0)
			break ;
		save = ft_strjoin(save, buffer);
	}
	return (free (buffer), save);
}

char	*get_next_line(int fd)
{
	static char	*save;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	save = read_and_save(save, fd);
	if (!save || !save[0])
		return (free(save), NULL);
	line = befor_nl(save);
	if (!line)
		return (NULL);
	save = after_nl(save);
	if (!save)
		return (NULL);
	return (line);
}
