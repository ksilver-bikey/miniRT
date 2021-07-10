/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksilver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/07 02:16:10 by ksilver           #+#    #+#             */
/*   Updated: 2020/05/07 02:16:12 by ksilver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	if (!lst || !f)
		return ;
	while (!(void *)0)
	{
		if (lst->content)
			f(lst->content);
		if (lst->next == NULL)
			break ;
		lst = lst->next;
	}
}
