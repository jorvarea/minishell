/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorvarea <jorvarea@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 16:38:27 by jorvarea          #+#    #+#             */
/*   Updated: 2024/07/25 01:29:27 by jorvarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	manage_and(t_shell *shell, t_cmd **cmd)
{
	int	status;

	waitpid((*cmd)->prev->pid, &status, 0);
	update_exit_status_process(shell, status);
	if (shell->exit_status != 0)
		*cmd = (*cmd)->next;
}

static void	manage_or(t_shell *shell, t_cmd **cmd)
{
	int	status;

	waitpid((*cmd)->prev->pid, &status, 0);
	update_exit_status_process(shell, status);
	if (shell->exit_status == 0)
		*cmd = (*cmd)->next;
}

void	exec(t_shell *shell, t_cmd *head, t_cmd *end_node)
{
	t_cmd	*cmd;

	cmd = head;
	while (cmd != end_node)
	{
		if (cmd->type == CMD)
			exec_one(shell, cmd);
		else if (cmd->type == AND)
			manage_and(shell, &cmd);
		else if (cmd->type == OR)
			manage_or(shell, &cmd);
		else if (cmd->type == OPEN_PAR)
			manage_parenthesis(shell, &cmd->next);
		cmd = cmd->next;
	}
	wait_pids(shell, head, end_node);
}
