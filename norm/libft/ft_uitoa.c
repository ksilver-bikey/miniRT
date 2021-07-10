/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uitoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksilver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/07 03:36:05 by ksilver           #+#    #+#             */
/*   Updated: 2020/05/07 03:36:07 by ksilver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	itoa_write(unsigned long long int nb, char *res, int len)
{
	size_t	div;

	div = 1;
	while (len > 1)
	{
		div = div * 10;
		len--;
	}
	len = 0;
	while (div > 0)
	{
		res[len] = (char)((nb / div) + '0');
		len++;
		nb = nb % div;
		div = div / 10;
	}
	res[len] = '\0';
}

char		*ft_uitoa(unsigned long long int n)
{
	unsigned long long int	nb;
	unsigned long long int	temp;
	int						len;
	char					*res;

	nb = n;
	len = 0;
	temp = nb;
	while (temp > 0)
	{
		temp = temp / 10;
		len++;
	}
	if (nb == 0)
		len++;
	if (!(res = (char *)ft_calloc(1, len + 2)))
		return (NULL);
	itoa_write(nb, res, len);
	return (res);
}
