/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksilver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/07 03:02:38 by ksilver           #+#    #+#             */
/*   Updated: 2020/05/07 03:02:39 by ksilver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t len)
{
	int				cnt;
	unsigned char	*destn;
	unsigned char	*sours;

	cnt = (int)len - 1;
	if (!dest && !src)
		return (NULL);
	sours = (unsigned char *)src;
	destn = (unsigned char *)dest;
	if (dest > src)
	{
		while (cnt > -1)
		{
			destn[cnt] = sours[cnt];
			cnt--;
		}
	}
	else if (dest < src)
		ft_memcpy(dest, src, len);
	return (destn);
}
