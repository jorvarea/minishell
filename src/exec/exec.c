/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorvarea <jorvarea@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 16:38:27 by jorvarea          #+#    #+#             */
/*   Updated: 2024/07/21 14:38:46 by jorvarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exec_one(t_shell *shell, t_cmd *cmd)
{
	execute_redir(shell, cmd);
	exit(shell->exit_status);
}

static void	exec_last(t_shell *shell, t_cmd *cmd, int original_stdout)
{
	pid_t	pid;
	int		status;

	safe_dup2(original_stdout, STDOUT_FILENO);
	pid = safe_fork();
	if (pid == 0)
		exec_one(shell, cmd);
	else
	{
		close(original_stdout);
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			shell->exit_status = WEXITSTATUS(status);
		else
			shell->exit_status = 128 + WTERMSIG(status);
	}
}

static void exec_left(t_shell *shell, t_cmd *cmd, int pipe_fds[2])
{
	close(pipe_fds[0]);
	safe_dup2(pipe_fds[1], STDOUT_FILENO);
	close(pipe_fds[1]);
	exec_one(shell, cmd->prev);
}

void	exec(t_shell *shell, t_cmd *cmd, int original_stdout)
{
	pid_t	pid;
	int		pipe_fds[2];

	if (!cmd->next)
	{
		exec_last(shell, cmd, original_stdout);
		return ;
	}
	cmd = cmd->next;
	safe_pipe(pipe_fds);
	pid = safe_fork();
	if (pid == 0)
		exec_left(shell, cmd, pipe_fds);
	else
	{
		close(pipe_fds[1]);
		safe_dup2(pipe_fds[0], STDIN_FILENO);
		close(pipe_fds[0]);
		exec(shell, cmd->next, original_stdout);
		waitpid(pid, NULL, 0);
	}
}
