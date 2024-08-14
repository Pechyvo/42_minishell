/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anonymous <anonymous@example.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/26 00:00:00 by anonymous         #+#    #+#             */
/*   Updated: 2026/07/26 00:00:00 by anonymous        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

void	ft_create_cmd(t_mhell *mhell)
{
	int	i = 0;
	while (i < mhell->tkn_l)
	{
		printf("Token: %s\tType: %d\n", mhell->tkn[i].token, mhell->tkn[i].type);
		i++;
	}
}

// < in ls -l | wc -c > out | cat << g | echo "Hello World!" >> out | echo "No $PWD" | echo 'Yes $SHLVL'