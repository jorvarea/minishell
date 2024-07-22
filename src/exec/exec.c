/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorvarea <jorvarea@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 16:38:27 by jorvarea          #+#    #+#             */
/*   Updated: 2024/07/22 02:19:09 by jorvarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h" 

static void	exec_left(t_shell *shell, t_cmd *cmd, int pipe_fds[2])
{
	safe_dup2(pipe_fds[1], STDOUT_FILENO);
	close(pipe_fds[1]);
	execute_redir(shell, cmd->prev);
	close(pipe_fds[0]);
	exit(shell->exit_status);
}

void	exec(t_shell *shell, t_cmd *cmd, int original_stdout)
{
	pid_t	pid;
	int		pipe_fds[2];

	if (!cmd->next)
	{
		close(pipe_fds[1]);
		safe_dup2(original_stdout, STDOUT_FILENO);
        close(original_stdout);
        execute_redir(shell, cmd);
		close(STDIN_FILENO);
		close(STDOUT_FILENO);
        return ;
	}
	if (cmd->type == CMD)
		cmd = cmd->next;
	safe_pipe(pipe_fds);
	pid = safe_fork();
	if (pid == 0)
		exec_left(shell, cmd, pipe_fds);
	else
	{
		safe_dup2(pipe_fds[0], STDIN_FILENO);
		close(pipe_fds[0]);
		exec(shell, cmd->next, original_stdout);
		close(pipe_fds[1]);
		waitpid(pid, NULL, 0);
	}
}
