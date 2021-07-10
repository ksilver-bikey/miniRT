/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksilver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/07 02:56:42 by ksilver           #+#    #+#             */
/*   Updated: 2020/05/07 02:56:45 by ksilver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *src, size_t len)
{
	unsigned char	*str;

	if (len == 0)
		return ;
	str = (unsigned char *)src;
	len--;
	while (len > 0)
	{
		str[len] = 0;
		len--;
	}
	str[0] = 0;
}
