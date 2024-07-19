/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorvarea <jorvarea@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 16:38:27 by jorvarea          #+#    #+#             */
/*   Updated: 2024/07/20 00:52:18 by jorvarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exec_one(t_shell *shell, t_cmd *cmd)
{
	pid_t	pid;
	int		status;

	pid = safe_fork();
	if (pid == 0)
		execute_redir(shell, cmd);
	wait(&status);
	if (WIFEXITED(status))
		shell->exit_status = WEXITSTATUS(status);
	else
		shell->exit_status = 130;
}

void	exec(t_shell *shell, t_cmd *cmd, int original_stdout)
{
	pid_t	pid;
	int		pipe_fds[2];

	if (!cmd->next)
	{
		safe_dup2(original_stdout, STDOUT_FILENO);
		exec_one(shell, cmd);
		close(original_stdout);
		return ;
	}
	else
		cmd = cmd->next;
	safe_pipe(pipe_fds);
	pid = safe_fork();
	if (pid == 0)
	{
		safe_dup2(pipe_fds[1], STDOUT_FILENO);
		if (cmd->prev->prev && cmd->prev->prev->type == PIPE)
			safe_dup2(pipe_fds[0], STDIN_FILENO);
		close(pipe_fds[0]);
		close(pipe_fds[1]);
		exec_one(shell, cmd->prev);
		exec(shell, cmd->next, original_stdout);
	}
	close(pipe_fds[0]);
	close(pipe_fds[1]);
	wait(NULL);
}
