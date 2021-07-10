/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksilver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/04 16:10:51 by ksilver           #+#    #+#             */
/*   Updated: 2020/05/04 16:11:08 by ksilver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		part_cnt(char const *str, char c, char **massif)
{
	int		i;
	int		start;
	int		parts_cnt;

	i = 0;
	parts_cnt = 0;
	while (str[i] != 0)
	{
		if (str[i] != c)
		{
			(massif != NULL) ? (start = i) : (i);
			while (str[i] != c && str[i] != 0)
				i++;
			if (massif)
			{
				massif[parts_cnt] = ft_substr(str, start, (i - start));
				if (massif[parts_cnt] == NULL)
					return (parts_cnt);
			}
			parts_cnt++;
		}
		else
			i++;
	}
	return (parts_cnt);
}

static void		clean_it(char **massif, int massif_checker)
{
	while (massif_checker > -1)
	{
		free_gc(massif[massif_checker]);
		massif_checker--;
	}
	free_gc(massif);
}

char			**ft_split(char const *s, char c)
{
	char	**massif;
	int		massif_size;
	int		massif_checker;

	massif = NULL;
	if (!s)
		return (NULL);
	if (!c)
		c = 0;
	massif_size = part_cnt(s, c, massif);
	if (!(massif = (char **)malloc_gc(sizeof(char *) * (massif_size + 1))))
		return (NULL);
	massif[massif_size] = NULL;
	massif_checker = part_cnt(s, c, massif);
	if (massif_checker != massif_size)
	{
		clean_it(massif, massif_checker);
		return (NULL);
	}
	return (massif);
}
