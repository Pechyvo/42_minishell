/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_destructors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 14:12:49 by escura            #+#    #+#             */
/*   Updated: 2024/05/25 16:42:48 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_alloc.h"

void	ft_free(void *ptr)
{
	t_allocs	*lst;
	t_allocs	*tmp;

	if(ptr == NULL)
		return ;
	lst = ft_allocs(NULL);
	tmp = NULL;
	while (lst != NULL)
	{
		if (lst->ptr == ptr)
		{
			tmp->next = lst->next;
			free(lst->ptr);
			free(lst);
			return ;
		}
		tmp = lst;
		lst = lst->next;
	}
}

void	ft_destructor(void)
{
	t_allocs	*lst;
	t_allocs	*temp;

	lst = ft_allocs(NULL);
	if (DEBUG)
		printf("Passing %d allocations to destructor\n", ft_allocsize());
	while (lst != NULL)
	{
		temp = lst;
		lst = lst->next;
		if (temp->ptr != NULL)
		{
			if (DEBUG)
				printf("Freeing using destructor %p\n", temp->ptr);
			free(temp->ptr);
			temp->ptr = NULL;
		}
		free(temp);
	}
	free(lst);
}
