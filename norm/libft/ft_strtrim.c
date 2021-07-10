/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksilver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/07 03:46:14 by ksilver           #+#    #+#             */
/*   Updated: 2020/05/07 03:46:18 by ksilver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		check_it(char letter, char const *set)
{
	int	i;

	i = 0;
	while (set[i] != 0)
	{
		if (set[i] == letter)
			return (1);
		i++;
	}
	return (0);
}

static int		checker(char const *s1, char const *set, char dir)
{
	int	i;

	i = 0;
	if (dir == 'f')
		i = ft_strlen(s1) - 1;
	while (s1[i] != 0)
	{
		if (check_it(s1[i], set) == 1)
		{
			if (dir == 'f')
				i--;
			else
				i++;
		}
		else
			return (i);
	}
	return (i);
}

char			*ft_strtrim(char *s1, char const *set)
{
	int		start;
	int		finish;
	char	*str;

	str = NULL;
	if (!s1)
		return (str);
	if (!set)
		return (s1);
	start = checker(s1, set, 's');
	if (s1[start] == '\0')
		return (ft_strdup("\0"));
	finish = checker(s1, set, 'f');
	str = ft_substr(s1, start, finish - start + 1);
	return (str);
}
