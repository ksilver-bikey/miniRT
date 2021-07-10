/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksilver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/07 02:58:36 by ksilver           #+#    #+#             */
/*   Updated: 2020/05/07 02:58:39 by ksilver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t number, size_t size)
{
	void		*ptr;

	ptr = NULL;
	if (number == 0 || size == 0)
	{
		number = 1;
		size = 1;
	}
	if (!(ptr = (void *)malloc_gc(number * size)))
		return (NULL);
	ft_bzero(ptr, number * size);
	return (ptr);
}
