/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anonymous <anonymous@example.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/26 00:00:00 by anonymous         #+#    #+#             */
/*   Updated: 2026/07/26 00:00:00 by anonymous        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

void	ft_cmdadd_back(t_cmd **lst, t_cmd *new)
{
	t_cmd	*tmp;

	if (lst)
	{
		if (*lst == NULL)
			*lst = new;
		else
		{
			tmp = ft_cmdlast(*lst);
			tmp->next = new;
		}
	}
}

t_cmd	*ft_cmdlast(t_cmd *lst)
{
	while (lst)
	{
		if (!lst->next)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}

void	ft_cmdclear(t_cmd **lst, void (*del)(void*))
{
	t_cmd	*tmp;

	if (lst)
	{
		while (*lst)
		{
			tmp = (*lst)->next;
			ft_cmddelone(*lst, del);
			*lst = tmp;
		}
	}
}

void	ft_cmddelone(t_cmd *lst, void (*del)(void*))
{
	if (lst == NULL || del == NULL)
		return ;
	del(lst->args);
	del(lst->in_rd);
	del(lst->out_rd);
	ft_free(lst);
}
