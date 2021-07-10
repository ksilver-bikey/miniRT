/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksilver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/07 03:02:12 by ksilver           #+#    #+#             */
/*   Updated: 2020/05/07 03:02:14 by ksilver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	size_t	num;
	int		sign;
	int		i;

	num = 0;
	i = 0;
	sign = 1;
	if (str[0] == 0)
		return (num);
	while ((8 < str[i] && str[i] < 14) || str[i] == 32)
		i++;
	(str[i] == 45) ? (sign = -1) : (sign);
	(str[i] == 45 || str[i] == 43) ? (i++) : (i);
	while (ft_isdigit(str[i]))
	{
		num = num * 10 + (str[i] - 48);
		if ((num) == 9223372036854775807)
			return ((sign == -1) ? (int)(1) : (int)(-1));
		if (num > 9223372036854775807)
			return ((sign == -1) ? (int)(0) : (int)(-1));
		i++;
	}
	return ((int)(num * sign));
}
