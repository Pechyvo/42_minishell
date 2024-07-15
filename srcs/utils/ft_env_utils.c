/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anonymous <anonymous@example.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/26 00:00:00 by anonymous         #+#    #+#             */
/*   Updated: 2026/07/26 00:00:00 by anonymous        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

t_env	*ft_find_env(t_env *env, char *var)
{
	size_t	len;

	len = ft_strlen(var);
	while (env)
	{
		if (len == ft_strlen(env->var) && !ft_strncmp(var, env->var, len))
			return (env);
		env = env->next;
	}
	return (NULL);
}
