/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksilver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/07 03:33:23 by ksilver           #+#    #+#             */
/*   Updated: 2020/05/07 03:33:25 by ksilver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*str;
	int		cnt;

	str = NULL;
	if (!s || !f)
		return (str);
	cnt = ft_strlen(s);
	if (!(str = (char *)malloc_gc(cnt + 1)))
		return (NULL);
	str[cnt] = 0;
	cnt--;
	while (cnt > -1)
	{
		str[cnt] = f(cnt, s[cnt]);
		cnt--;
	}
	return (str);
}
