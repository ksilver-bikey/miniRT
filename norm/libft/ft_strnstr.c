/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksilver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/07 03:37:41 by ksilver           #+#    #+#             */
/*   Updated: 2020/05/07 03:37:43 by ksilver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(char *big, const char *ltl, size_t len)
{
	size_t	b;
	size_t	l;
	size_t	ltl_len;

	b = 0;
	if (!big || !ltl)
		return (NULL);
	if (!(ltl_len = ft_strlen(ltl)))
		return (big);
	ltl_len--;
	while (b + ltl_len < len && big[b] != 0)
	{
		if (big[b] == ltl[0] && ltl[ltl_len] == big[b + ltl_len])
		{
			l = 0;
			while (ltl[l] != 0 && big[b + l] == ltl[l] && b + l < len)
				l++;
			if (ltl[l] == 0)
				return (&big[b]);
		}
		b++;
	}
	return (NULL);
}
