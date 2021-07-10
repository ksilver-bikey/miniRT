/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksilver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/07 02:27:18 by ksilver           #+#    #+#             */
/*   Updated: 2020/05/07 02:28:34 by ksilver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstnew(void *content)
{
	t_list	*new_elem;

	if (!(new_elem = malloc_gc(sizeof(t_list))))
		return (NULL);
	if (content)
		new_elem->content = content;
	else
		new_elem->content = NULL;
	new_elem->next = NULL;
	return (new_elem);
}
