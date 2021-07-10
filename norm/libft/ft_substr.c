/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksilver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/07 03:37:53 by ksilver           #+#    #+#             */
/*   Updated: 2020/05/07 03:37:56 by ksilver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*ft_substr(char const *s, size_t start, size_t len)
{
	char	*str;
	size_t	str_full_len;

	str = NULL;
	str_full_len = ((s) ? (ft_strlen(s)) : (0));
	if (str_full_len < start)
		len = 0;
	if (len > str_full_len - start)
		len = str_full_len - start;
	if (!(str = (char *)ft_calloc(sizeof(char), (len + 3))))
		return (NULL);
	if (len > 0)
		ft_strlcpy(str, &s[start], len + 1);
	return (str);
}
