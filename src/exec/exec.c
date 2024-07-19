/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorvarea <jorvarea@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 16:38:27 by jorvarea          #+#    #+#             */
/*   Updated: 2024/07/19 22:00:42 by jorvarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exec_last(t_shell *shell, t_cmd *cmd, t_pids_array *child_pids)
{
	pid_t	pid;
	int		pipe_fds[2];

	safe_pipe(pipe_fds);
	pid = safe_fork();
	if (pid == 0)
	{
		close(pipe_fds[1]);
		if (cmd->prev->prev && cmd->prev->prev->type == PIPE)
			safe_dup2(pipe_fds[0], STDIN_FILENO);
		close(pipe_fds[0]);
		execute_redir(shell, cmd);
		exit(0);
	}
	close(pipe_fds[0]);
	close(pipe_fds[1]);
	add_child_pid(child_pids, pid);
}

void	exec(t_shell *shell, t_cmd *cmd)
{
	t_pids_array	child_pids;

	init_pids_array(&child_pids);
	while (cmd)
	{
		if (cmd->type == PIPE)
			exec_pipe(shell, cmd, &child_pids);
		if (!cmd->next)
			exec_last(shell, cmd, &child_pids);
		cmd = cmd->next;
	}
	wait_children(shell, &child_pids);
}
