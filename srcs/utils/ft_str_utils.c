/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anonymous <anonymous@example.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/26 00:00:00 by anonymous         #+#    #+#             */
/*   Updated: 2026/07/26 00:00:00 by anonymous        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

bool	ft_is_empty(char *str)
{
	if (!str)
		return (true);
	while (*str && ft_is_space(*str))
		str++;
	if (*str)
		return (false);
	return (true);
}

bool	ft_is_space(char c)
{
	return (c == '\t' || c == ' ');
}

void	ft_skip_spaces(char **str)
{
	while (ft_is_space(**str))
		*str += 1;
}

bool	ft_is_quote(char c)
{
	return (c == '\'' || c == '"');
}

void	ft_quote_state(int c, int *state)
{
	if (c == '\'')
	{
		if (*state == 1)
			*state = 0;
		else if (*state == 0)
			*state = 1;
	}
	if (c == '\"')
	{
		if (*state == 2)
			*state = 0;
		else if (*state == 0)
			*state = 2;
	}
}
