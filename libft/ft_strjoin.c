/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melmarti <melmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 18:39:40 by melmarti          #+#    #+#             */
/*   Updated: 2024/11/04 13:38:29 by melmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	int		i;
	int		j;
	int		total;
	char	*s3;

	if (!s1 || !s2)
		return (NULL);
	total = ft_strlen(s1) + ft_strlen(s2);
	s3 = malloc(sizeof(char) * total + 1);
	if (!s3)
		return (NULL);
	i = 0;
	while (s1[i] && i < total)
	{
		s3[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j] && i < total + 1)
		s3[i++] = s2[j++];
	s3[i] = '\0';
	return (s3);
}

char	*ft_strjoin_free(char *s1, const char *s2)
{
	size_t	i;
	size_t	j;
	size_t	total;
	char	*s3;

	if (!s1 || !s2)
		return (NULL);
	total = 0;
	total = ft_strlen(s1);
	total += ft_strlen(s2);
	s3 = malloc(sizeof(char) * total + 1);
	if (!s3)
		return (NULL);
	i = -1;
	while (s1[++i] && i < total)
		s3[i] = s1[i];
	j = 0;
	while (s2[j] && i < total + 1)
		s3[i++] = s2[j++];
	s3[i] = '\0';
	if (s1)
		free(s1);
	return (s3);
}
