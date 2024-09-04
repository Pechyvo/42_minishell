/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clear.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anonymous <anonymous@example.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/26 00:00:00 by anonymous         #+#    #+#             */
/*   Updated: 2026/07/26 00:00:00 by anonymous        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "../../incl/minishell.h"

static void	ft_clear_tkn(t_tkn **tkn, int *len);

void	ft_free_mhell_data(t_mhell *mhell)
{
	if (mhell->tkn && mhell->tkn_l)
		ft_clear_tkn(&mhell->tkn, &mhell->tkn_l);
	if (mhell->cmd)
	{
		ft_cmdclear(&mhell->cmd, ft_free);
		mhell->cmd_l = 0;
	}
	// printf("Cleared\n");
	// ft_print_cmd(mhell->cmd);
}

static void	ft_clear_tkn(t_tkn **tkn, int *len)
{
	int	i;

	i = 0;
	while (i < *len && (*tkn)[i].token)
	{
		ft_free((*tkn)[i].token);	
		i++;
	}
	if (*len)
		ft_free(*tkn);
	*tkn = NULL;
	*len = 0;
}
