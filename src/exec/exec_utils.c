/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorvarea <jorvarea@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 21:00:35 by jorvarea          #+#    #+#             */
/*   Updated: 2024/07/23 17:44:04 by jorvarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	peek_pipes(t_cmd *cmd)
{
	int	pipes_fd[2];

	if (cmd->next && cmd->next->type == PIPE)
	{
		safe_pipe(pipes_fd);
		cmd->outfd = pipes_fd[1];
		cmd->next->next->infd = pipes_fd[0];
	}
}

static void	manage_pipes_cmd(t_cmd *cmd)
{
	if (cmd->infd != -1)
	{
		dup2(cmd->infd, STDIN_FILENO);
		close(cmd->infd);
	}
	if (cmd->outfd != -1)
	{
		dup2(cmd->outfd, STDOUT_FILENO);
		close(cmd->outfd);
	}
	if (cmd->next && cmd->next->type == PIPE)
		close(cmd->next->next->infd);
}

void	exec_one(t_shell *shell, t_cmd *cmd)
{
	pid_t	pid;

	peek_pipes(cmd);
	pid = safe_fork();
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		manage_pipes_cmd(cmd);
		execute_redir(shell, cmd);
		exit(shell->exit_status);
	}
	else
	{
		cmd->pid = pid;
		if (cmd->outfd >= 0)
			close(cmd->outfd);
		if (cmd->infd >= 0)
			close(cmd->infd);
	}
}

void	wait_pids(t_shell *shell, t_cmd *cmd)
{
	int	status;

	while (cmd)
	{
		if (cmd->pid != -1)
		{
			waitpid(cmd->pid, &status, 0);
			if (WIFEXITED(status))
				shell->exit_status = WEXITSTATUS(status);
			else
				shell->exit_status = 130;
			cmd = cmd->next;
		}
	}
}

void	init_fds_pid(t_cmd *cmd)
{
	while (cmd)
	{
		if (cmd->type == CMD)
		{
			cmd->infd = -1;
			cmd->outfd = -1;
			cmd->pid = -1;
		}
		cmd = cmd->next;
	}
}
