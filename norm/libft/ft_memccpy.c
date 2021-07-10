/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksilver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/07 03:50:45 by ksilver           #+#    #+#             */
/*   Updated: 2020/05/07 03:50:47 by ksilver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(const void *dest, const void *src, int ch, size_t len)
{
	size_t			cnt;
	unsigned char	*destination;
	unsigned char	*source;
	unsigned char	character;

	destination = (unsigned char *)dest;
	source = (unsigned char *)src;
	character = ch;
	cnt = 0;
	while (cnt < len)
	{
		(destination[cnt] = source[cnt]);
		if (source[cnt] == character)
			return (&destination[cnt + 1]);
		cnt++;
	}
	return (NULL);
}
