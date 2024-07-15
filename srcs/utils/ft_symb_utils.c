/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_symb_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anonymous <anonymous@example.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/26 00:00:00 by anonymous         #+#    #+#             */
/*   Updated: 2026/07/26 00:00:00 by anonymous        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int ft_space(char c)
{
	return (c == ' ' || c == '\t');
}

int ft_quote(char c)
{
	if (c == '\"')
		return ('\"');
	if (c == '\'')
		return ('\'');
	return (0);
}

void	ft_quote_type(char c, char *q)
{
	if ((ft_quote(c)) && !*q)
		*q = c;
	else if ((ft_quote(c)) && *q == c)
		*q = '\0';
}
