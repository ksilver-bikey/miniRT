/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksilver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/07 03:19:01 by ksilver           #+#    #+#             */
/*   Updated: 2020/05/07 03:19:03 by ksilver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dst_cnt;
	size_t	src_cnt;
	size_t	ret_cnt;

	dst_cnt = ft_strlen(dst);
	src_cnt = ft_strlen(src);
	ret_cnt = (size <= dst_cnt) ? (src_cnt + size) : (dst_cnt + src_cnt);
	src_cnt = 0;
	while (src[src_cnt] != 0 && dst_cnt + 1 < size)
	{
		dst[dst_cnt] = src[src_cnt];
		src_cnt++;
		dst_cnt++;
	}
	dst[dst_cnt] = '\0';
	return (ret_cnt);
}
