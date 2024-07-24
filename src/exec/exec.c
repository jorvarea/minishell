/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorvarea <jorvarea@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 16:38:27 by jorvarea          #+#    #+#             */
/*   Updated: 2024/07/24 12:41:57 by jorvarea         ###   ########.fr       */
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

void	exec(t_shell *shell)
{
	t_cmd	*cmd;

	cmd = shell->tokens;
	init_fds_pid(cmd);
	while (cmd)
	{
		if (cmd->type == CMD)
			exec_one(shell, cmd);
		else if (cmd->type == AND)
			manage_and(shell, &cmd);
		else if (cmd->type == OR)
			manage_or(shell, &cmd);
		cmd = cmd->next;
	}
	wait_pids(shell, shell->tokens);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
}
