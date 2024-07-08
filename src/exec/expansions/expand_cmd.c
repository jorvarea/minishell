/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorvarea <jorvarea@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 13:03:19 by jorvarea          #+#    #+#             */
/*   Updated: 2024/07/08 11:26:44 by jorvarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef enum e_inner_quotes
{
	NONE = 0,
	SINGLE = 1,
	DOUBLE = 2,
}					t_inner_quotes;

typedef struct s_quotes
{
	bool			single_quotes;
	bool			double_quotes;
	t_inner_quotes	inner_q;
}					t_quotes;

void	manage_quotes(char char_quotes, t_quotes *quotes)
{
	if (char_quotes == '\'')
	{
		quotes->single_quotes = !quotes->single_quotes;
		quotes->inner_q = SINGLE;
	}
	else if (char_quotes == '\"')
	{
		quotes->double_quotes = !quotes->double_quotes;
		quotes->inner_q = DOUBLE;
	}
}

static void	expand_arg(t_shell *shell, char **ptr_arg)
{
	t_quotes	quotes;
	char		*arg;
	int			i;

	arg = *ptr_arg;
	ft_memset(&quotes, 0, sizeof(quotes));
	i = 0;
	while (arg[i])
	{
		if (arg[i] == '\'' || arg[i] == '\"')
			manage_quotes(arg[i], &quotes);
		else if (arg[i] == '~' && !quotes.single_quotes && !quotes.double_quotes
			&& i == 0 && (arg[i + 1] == '/' || arg[i + 1] == '\0'))
			replace_home(shell, ptr_arg, i);
		else if (arg[i] == '$' && arg[i + 1] == '?' && !quotes.single_quotes)
			replace_exit_status(shell, ptr_arg, i);
		else if (arg[i] == '$' && (!quotes.single_quotes
				|| (quotes.double_quotes && quotes.inner_q == SINGLE)))
			replace_env(shell, ptr_arg, i);
		else if (arg[i] == '*' && !quotes.single_quotes
			&& !quotes.double_quotes)
			replace_wildcard(shell, ptr_arg, i);
		arg = *ptr_arg;
		i++;
	}
}

void	expand_cmd(t_shell *shell, char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		expand_arg(shell, &args[i]);
		i++;
	}
}
