/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksilver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/07 03:22:20 by ksilver           #+#    #+#             */
/*   Updated: 2020/05/07 03:22:23 by ksilver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(char *s, int ch)
{
	int				cnt;
	unsigned char	c;

	cnt = ft_strlen(s);
	c = (unsigned char)ch;
	while (cnt > -1)
	{
		if (s[cnt] == c)
			return (&s[cnt]);
		cnt--;
	}
	return (NULL);
}
