/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_parse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anonymous <anonymous@example.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/26 00:00:00 by anonymous         #+#    #+#             */
/*   Updated: 2026/07/26 00:00:00 by anonymous        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

bool	ft_input_parse(t_mhell *mhell, char *input)
{
	char	*cmd_line;

	(void)mhell;
	while (*input)
	{
		ft_skip_spaces(&input);
		cmd_line = input;
		// ft_find_next_cmd(cmd, &input, &cmd_line);
	}
	return (true);
}
