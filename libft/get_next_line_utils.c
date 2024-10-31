/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albestae <albestae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 09:33:16 by albestae          #+#    #+#             */
/*   Updated: 2024/10/31 11:32:29 by albestae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

size_t	gnl_strlen(const char *str)
{
	size_t	i;

	if (str == NULL)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*gnl_strchr(const char *s, int c)
{
	if (s == NULL)
		return (NULL);
	if (c == '\0')
		return ((char *)(s + ft_strlen(s)));
	while (*s)
	{
		if ((unsigned char)*s == (unsigned char)c)
			return ((char *)s);
		s++;
	}
	return (NULL);
}

char	*gnl_strdup(char *s)
{
	unsigned char	*tab;
	unsigned char	*t;

	if (!s)
		return (NULL);
	tab = (unsigned char *)malloc(sizeof(char) * ft_strlen(s) + 1);
	if (tab == NULL)
		return (NULL);
	t = tab;
	while (*s != '\0')
		*tab++ = *s++;
	*tab = '\0';
	return ((char *)t);
}

char	*gnl_strjoin(char *s1, char *s2)
{
	char	*tab;
	char	*p;
	char	*t;

	if (!s1)
		return (gnl_strdup(s2));
	tab = (char *)malloc((ft_strlen(s1) + ft_strlen(s2)) * sizeof(char) + 1);
	if (tab == NULL)
		return (NULL);
	p = tab;
	t = s1;
	while (*s1)
		*(tab++) = *(s1++);
	while (*s2)
		*(tab++) = *(s2++);
	*tab = '\0';
	free(t);
	return (p);
}
