/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksilver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/07 03:11:40 by ksilver           #+#    #+#             */
/*   Updated: 2020/05/07 03:11:45 by ksilver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t len)
{
	size_t			cnt;
	unsigned char	*destn;
	unsigned char	*sours;

	if (!dest && !src)
		return (NULL);
	destn = (unsigned char *)dest;
	sours = (unsigned char *)src;
	cnt = 0;
	while (cnt < len)
	{
		destn[cnt] = sours[cnt];
		cnt++;
	}
	return (destn);
}
