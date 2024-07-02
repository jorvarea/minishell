/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorvarea <jorvarea@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 13:03:19 by jorvarea          #+#    #+#             */
/*   Updated: 2024/07/02 21:03:18 by jorvarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef enum e_inner_quotes
{
	NONE = 0,
	SINGLE = 1,
	DOUBLE = 2,
}			t_inner_quotes;

void	manage_quotes(char quotes, bool *single_quotes, bool *double_quotes,
		t_inner_quotes *inner_q)
{
	if (quotes == '\'')
	{
		*single_quotes = !*single_quotes;
		*inner_q = SINGLE;
	}
	else if (quotes == '\"')
	{
		*double_quotes = !*double_quotes;
		*inner_q = DOUBLE;
	}
}

static void	expand_arg(t_shell *shell, char **ptr_arg, bool *single_quotes,
		bool *double_quotes)
{
	t_inner_quotes	inner_q;
	char			*arg;
	int				i;

	arg = *ptr_arg;
	inner_q = NONE;
	i = 0;
	while (arg[i])
	{
		if (arg[i] == '\'' || arg[i] == '\"')
			manage_quotes(arg[i], single_quotes, double_quotes, &inner_q);
		else if (arg[i] == '~' && !*single_quotes && !*double_quotes && i == 0
			&& (arg[i + 1] == '/' || arg[i + 1] == '\0'))
			replace_home(shell, ptr_arg, i);
		else if (arg[i] == '$' && arg[i + 1] == '?' && !*single_quotes)
			replace_exit_status(shell, ptr_arg, i);
		else if (arg[i] == '$' && (!*single_quotes || 
				(*double_quotes && inner_q == SINGLE)))
			replace_env(shell, ptr_arg, i);
		else if (arg[i] == '*' && !*single_quotes && !*double_quotes)
			replace_wildcard(shell, ptr_arg, i);
		arg = *ptr_arg;
		i++;
	}
}

void	expand_cmd(t_shell *shell, char **args)
{
	bool	single_quotes;
	bool	double_quotes;
	int		i;

	single_quotes = false;
	double_quotes = false;
	i = 0;
	while (args[i])
	{
		expand_arg(shell, &args[i], &single_quotes, &double_quotes);
		i++;
	}
}
