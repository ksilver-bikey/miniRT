/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ulltoa_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksilver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/16 22:37:33 by ksilver           #+#    #+#             */
/*   Updated: 2020/07/15 19:27:24 by ksilver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_ulltoa_base(unsigned long long int n, char *base)
{
	char					*res;
	int						size;
	unsigned long long int	temp;
	unsigned int			base_len;

	size = 0;
	temp = n;
	base_len = ft_strlen(base);
	while (temp >= base_len)
	{
		temp = temp / base_len;
		++size;
	}
	temp = n;
	if (!(res = calloc(1, size + 2)))
		return (NULL);
	while (temp >= base_len)
	{
		res[size] = base[temp % base_len];
		temp = temp / base_len;
		size--;
	}
	res[size] = base[temp % base_len];
	return (res);
}
