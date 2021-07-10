/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_cpy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksilver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/24 15:59:56 by ksilver           #+#    #+#             */
/*   Updated: 2020/07/24 15:59:59 by ksilver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*dup_cpy(void *source, void *dst, int size)
{
	int				cnt;
	int				try;
	unsigned char	*src;
	unsigned char	*dest;

	cnt = 0;
	try = 3;
	dest = dst;
	src = source;
	while (dest == NULL && try--)
		dest = (unsigned char *)malloc_gc(size + 1);
	if (dest == NULL)
		return (NULL);
	while (cnt++ <= size)
		dest[cnt - 1] = '\0';
	cnt = 0;
	if (source)
	{
		while (cnt++ < size)
			dest[cnt - 1] = src[cnt - 1];
	}
	return (dest);
}
