/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksilver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/07 03:36:05 by ksilver           #+#    #+#             */
/*   Updated: 2020/05/07 03:36:07 by ksilver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	itoa_write(long long int nb, char sign, char *res, int len)
{
	size_t	div;

	div = 1;
	((sign == '-') ? (len--) : (len));
	while (len > 1)
	{
		div = div * 10;
		len--;
	}
	len = 0;
	(sign == '-') ? (res[len] = sign) : (res[len]);
	len = (sign == '-') ? (1) : (0);
	while (div > 0)
	{
		res[len] = (char)((nb / div) + '0');
		len++;
		nb = nb % div;
		div = div / 10;
	}
	res[len] = '\0';
}

char		*ft_itoa(long long int n)
{
	char			sign;
	long long int	nb;
	long long int	temp;
	int				len;
	char			*res;

	nb = n;
	sign = ((nb < 0) ? ('-') : ('+'));
	(nb < 0) ? (nb *= -1) : (nb);
	len = 0;
	temp = nb;
	while (temp > 0)
	{
		temp = temp / 10;
		len++;
	}
	if (nb == 0 || sign == '-')
		len++;
	if (!(res = (char *)ft_calloc(1, len + 2)))
		return (NULL);
	itoa_write(nb, sign, res, len);
	return (res);
}
