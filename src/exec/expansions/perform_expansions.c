/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perform_expansions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorvarea <jorvarea@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 13:03:19 by jorvarea          #+#    #+#             */
/*   Updated: 2024/07/01 21:04:15 by jorvarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	expand_arg(t_shell *shell, char *arg, bool *single_quotes,
		bool *double_quotes)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == '\'')
			single_quotes = !single_quotes;
		else if (arg[i] == '\"')
			double_quotes = !double_quotes;
		else if (arg[i] == '~' && !single_quotes && !double_quotes && i == 0
			&& (arg[i + 1] == '/' || arg[i + 1] == '\0'))
			replace_home(shell, &arg, i);
		else if (arg[i] == '$' && !single_quotes)
			replace_env(shell, &arg, i);
		else if (arg[i] == '*' && !single_quotes && !double_quotes)
			replace_wildcard(shell, &arg, i);
		i++;
	}
}

void	expand_cmd(t_shell *shell, char **args)
{
	bool	single_quotes;
	bool	double_quotes;
	int		i;
	int		j;

	single_quotes = false;
	double_quotes = false;
	i = 0;
	while (args[i])
	{
		expand_arg(shell, args[i], &single_quotes, &double_quotes);
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
