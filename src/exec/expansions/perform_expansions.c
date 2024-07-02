/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perform_expansions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorvarea <jorvarea@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 13:03:19 by jorvarea          #+#    #+#             */
/*   Updated: 2024/07/02 13:36:56 by jorvarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	expand_arg(t_shell *shell, char **ptr_arg, bool *single_quotes,
		bool *double_quotes)
{
	char	*arg;
	int		i;

	arg = *ptr_arg;
	i = 0;
	while (arg[i])
	{
		if (arg[i] == '\'')
			*single_quotes = !*single_quotes;
		else if (arg[i] == '\"')
			*double_quotes = !*double_quotes;
		else if (arg[i] == '~' && !*single_quotes && !*double_quotes && i == 0
			&& (arg[i + 1] == '/' || arg[i + 1] == '\0'))
			replace_home(shell, ptr_arg, i);
		else if (arg[i] == '$' && !*single_quotes)
			replace_env(shell, ptr_arg, i);
		else if (arg[i] == '*' && !*single_quotes && !*double_quotes)
			replace_wildcard(shell, ptr_arg, i);
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

void	perform_expansions(t_shell *shell, t_cmd *cmd_lst)
{
	t_cmd	*cmd;

	cmd = cmd_lst;
	while (cmd)
	{
		expand_cmd(shell, cmd->args);
		cmd = cmd->next;
	}
}
