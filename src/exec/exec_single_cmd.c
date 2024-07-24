/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_single_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorvarea <jorvarea@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 15:14:47 by jorvarea          #+#    #+#             */
/*   Updated: 2024/07/24 18:01:21 by jorvarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_built_in(t_cmd *cmd)
{
	char	*cmd_str;

	cmd_str = cmd->args[0];
	return (equal_str(cmd_str, "echo") || equal_str(cmd_str, "cd")
		|| equal_str(cmd_str, "env") || equal_str(cmd_str, "pwd")
		|| equal_str(cmd_str, "export") || equal_str(cmd_str, "unset")
		|| equal_str(cmd_str, "exit"));
}

void	exec_single_cmd(t_shell *shell)
{
	pid_t	pid;
	int		status;

	if (is_built_in(shell->tokens))
		execute_redir(shell, shell->tokens);
	else
	{
		pid = safe_fork();
		if (pid == 0)
		{
			signal(SIGINT, SIG_DFL);
			execute_redir(shell, shell->tokens);
			exit(shell->exit_status);
		}
		else
		{
			waitpid(pid, &status, 0);
			update_exit_status_process(shell, status);
			close(STDIN_FILENO);
			close(STDOUT_FILENO);
		}
	}
}
