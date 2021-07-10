/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   con_loc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksilver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 13:37:14 by ksilver           #+#    #+#             */
/*   Updated: 2020/09/14 13:37:16 by ksilver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_mem_list	**allocated_list(void)
{
	static	t_mem_list	*alloc_list = NULL;

	return (&alloc_list);
}

static int			mem_listadd_front(t_mem_list **lst, void **ptr)
{
	t_mem_list	*new;
	int			cnt;

	cnt = 3;
	new = NULL;
	if (!(*ptr) || !lst)
		return (0);
	while (new == NULL && cnt-- > 0)
		new = (t_mem_list *)malloc(sizeof(t_mem_list));
	if (new == NULL)
	{
		free(*ptr);
		free_all();
		write(2, "Error\nAllocation failed\n", 24);
		return (0);
	}
	new->obj = *ptr;
	new->next = *lst;
	*lst = new;
	return (1);
}

void				free_gc(void *ptr)
{
	t_mem_list	*runner;
	t_mem_list	*forward;

	if (!(runner = *(allocated_list())))
		return ;
	while (runner->next != NULL && runner->next->obj != ptr)
		runner = runner->next;
	if (runner->next != NULL && runner->next->obj == ptr)
	{
		forward = runner->next;
		runner->next = forward->next;
		free(forward->obj);
		free(forward);
	}
}

void				free_all(void)
{
	t_mem_list	*forward;
	t_mem_list	*backward;

	if (!(forward = *(allocated_list())))
		return ;
	while (forward->next != NULL)
	{
		backward = forward;
		forward = forward->next;
		if (backward->obj != NULL)
			free(backward->obj);
		free(backward);
	}
	if (forward->obj != NULL)
		free(forward->obj);
	free(forward);
}

void				*malloc_gc(int size)
{
	t_mem_list		**alloc_list;
	void			*ptr;
	int				cnt;
	unsigned char	*temp;

	ptr = NULL;
	cnt = 3;
	if (size == 0)
		size = 1;
	alloc_list = allocated_list();
	while (ptr == NULL && cnt-- > 0)
		ptr = (void *)malloc(size + 2);
	if (ptr == NULL)
	{
		free_all();
		write(2, "Allocation failed\n", 18);
		return (NULL);
	}
	mem_listadd_front(alloc_list, &ptr);
	cnt = -1;
	temp = ptr;
	while (++cnt < size)
		temp[cnt] = 0;
	return (ptr);
}
