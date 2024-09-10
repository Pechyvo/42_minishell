/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hrdc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anonymous <anonymous@example.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/26 00:00:00 by anonymous         #+#    #+#             */
/*   Updated: 2026/07/26 00:00:00 by anonymous        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

bool	ft_handle_heredocs(t_mhell *mhell)
{
	(void)mhell;
	return (true);
}

// void	heredoc_loop(t_mhell *mshell, int i)
// {
// 	int	j;

// 	j = 0;
// 	while (j < mshell->cmdarr[i].inp_l)
// 	{
// 		if (mshell->cmdarr[i].inp[j].type == _hrdc)
// 			heredoc(mshell, i, j);
// 		j++;
// 	}
// }

// void	heredoc(t_mhell *mshell, int i, int j)
// {
// 	char	*line;
// 	char	*limiter;
// 	int		tmp_fd;

// 	limiter = mshell->cmdarr[i].inp[j].word;
// 	tmp_fd = open("/tmp/heredoc_tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 	while (1)
// 	{
// 		line = readline("heredoc> ");
// 		if (!line || ft_strcmp(line, limiter) == 0)
// 		{
// 			free(line);
// 			break ;
// 		}
// 		write(tmp_fd, line, ft_strlen(line));
// 		write(tmp_fd, "\n", 1);
// 		free(line);
// 	}
// 	close(tmp_fd);
// }
