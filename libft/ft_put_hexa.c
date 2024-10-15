/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_hexa.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melmarti <melmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 13:24:55 by melmarti          #+#    #+#             */
/*   Updated: 2024/10/15 13:28:12 by melmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_put_hexa(unsigned int nbr)
{
	char	*base;
	int		count;

	count = 0;
	base = "0123456789abcdef";
	if (nbr > 15)
	{
		ft_put_hexa(nbr / 16);
		ft_put_hexa(nbr % 16);
	}
	else
	{
		write(1, &base[nbr], 1);
		count++;
	}
	return (count);
}