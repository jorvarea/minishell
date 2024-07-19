/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorvarea <jorvarea@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 20:51:09 by jorvarea          #+#    #+#             */
/*   Updated: 2024/07/19 22:00:47 by jorvarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_pipe(t_shell *shell, t_cmd *cmd, t_pids_array *child_pids)
{
	pid_t	pid;
	int		pipe_fds[2];

	safe_pipe(pipe_fds);
	pid = safe_fork();
	if (pid == 0)
	{
		safe_dup2(pipe_fds[1], STDOUT_FILENO);
		if (cmd->prev->prev && cmd->prev->prev->type == PIPE)
			safe_dup2(pipe_fds[0], STDIN_FILENO);
		close(pipe_fds[0]);
		close(pipe_fds[1]);
		execute_redir(shell, cmd->prev);
		exit(0);
	}
	close(pipe_fds[0]);
	close(pipe_fds[1]);
	add_child_pid(child_pids, pid);
}
