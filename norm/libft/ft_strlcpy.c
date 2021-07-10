/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksilver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/07 03:39:55 by ksilver           #+#    #+#             */
/*   Updated: 2020/05/07 03:39:59 by ksilver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	cnt;
	size_t	res;

	if (!dst || !src)
		return (0);
	res = ft_strlen(src);
	if (!size)
		return (res);
	cnt = (res + 1 < size) ? res : size - 1;
	ft_memcpy(dst, src, cnt);
	(size != 0) ? (dst[cnt] = '\0') : (cnt);
	return (res);
}
