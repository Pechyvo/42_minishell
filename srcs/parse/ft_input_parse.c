/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_input_parse.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalchuk <svalchuk@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 22:22:44 by svalchuk          #+#    #+#             */
/*   Updated: 2024/09/15 15:01:47 by svalchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

static char	*ft_trim_input(char *str);
static void	ft_prep_input(char **input, char *str);
static void	ft_replace_dollar(t_mhell *mhell, char **str);
static bool	ft_check_tokens(t_mhell *mhell);

bool	ft_input_parse(t_mhell *mhell)
{
	char	*input;

	if (!ft_input_error(mhell, mhell->cmd_line))
		return (false);
	input = ft_trim_input(mhell->cmd_line);
	ft_replace_dollar(mhell, &input);
	if (!*input)
		return (mhell->exit_code = 0, ft_free(input), false);
	ft_tokenize(mhell, input);
	if (!ft_check_tokens(mhell))
		return (mhell->exit_code = 2, ft_free(input), false);
	ft_open_quotes(mhell);
	ft_create_cmd(mhell);
	mhell->exit_code = 0;
	return (ft_free(input), true);
}

static char	*ft_trim_input(char *str)
{
	char	*input;
	int		state;
	int		len;
	int		i;

	i = 0;
	len = 0;
	state = 0;
	input = NULL;
	ft_prep_input(&input, str);
	while (str[i])
	{
		ft_quote_state(str[i], &state);
		if (!(state == 0 && (ft_conc_space(str[i], str[i + 1])
					|| (ft_is_space(str[i]) && (!len || !str[i + 1])))))
			input[len++] = str[i];
		i++;
	}
	return (str);
}

static void	ft_prep_input(char **input, char *str)
{
	int	state;
	int	len;
	int	i;

	i = 0;
	len = 0;
	state = 0;
	if (!str)
		return ;
	while (str[i])
	{
		ft_quote_state(str[i], &state);
		if (!(state == 0 && (ft_conc_space(str[i], str[i + 1])
					|| (ft_is_space(str[i]) && (!len || !str[i + 1])))))
			len++;
		i++;
	}
	*input = (char *)ft_calloc(sizeof(char), len + 1);
	if (!*input)
		exit(printf(ER ER_ALLOC));
}

static void	ft_replace_dollar(t_mhell *mhell, char **str)
{
	char	**arr;
	int		state;
	int		i;

	arr = ft_split_savediv(*str, '$');
	i = 0;
	state = 0;
	while (arr[i])
	{
		ft_substr_dollar(mhell, &arr[i], &state);
		i++;
	}
	ft_free(*str);
	*str = ft_arrjoin(arr);
	ft_free_array(arr);
}

static bool	ft_check_tokens(t_mhell *mhell)
{
	t_tkn	*tkn;
	int		i;

	i = 0;
	tkn = mhell->tkn;
	while (i < mhell->tkn_l)
	{
		if (tkn[i].type == _pipe && ((i - 1) < 0 || (i + 1) >= mhell->tkn_l))
			return (printf(ER_MHELL ER_SX_STR, tkn[i].token), false);
		else if (tkn[i].type > _pipe && (i + 1) >= mhell->tkn_l)
			return (printf(ER_MHELL ER_SX_STR, "newline"), false);
		else if (tkn[i].type > _pipe && mhell->tkn[i + 1].type > 1)
			return (printf(ER_MHELL ER_SX_STR, tkn[i + 1].token), false);
		else if (tkn[i].type == _pipe && tkn[i + 1].type == _pipe)
			return (printf(ER_MHELL ER_SX_STR, tkn[i + 1].token), false);
		i++;
	}
	return (true);
}
