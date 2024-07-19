/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_one.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorvarea <jorvarea@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 20:28:15 by jorvarea          #+#    #+#             */
/*   Updated: 2024/07/20 00:26:29 by jorvarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_built_in(t_cmd *cmd)
{
	char	**args;

	args = cmd->args;
	return (args && (equal_str(args[0], "echo") || equal_str(args[0], "pwd")
			|| equal_str(args[0], "env") || equal_str(args[0], "cd")
			|| equal_str(args[0], "export") || equal_str(args[0], "unset")));
}

void	exec_single_cmd(t_shell *shell, t_cmd *cmd)
{
	pid_t	pid;
	int		status;

	if (is_built_in(cmd))
		execute_redir(shell, cmd);
	else
	{
		pid = safe_fork();
		if (pid == 0)
		{
			execute_redir(shell, cmd);
			exit(0);
		}
		wait(&status);
		if (WIFEXITED(status))
			shell->exit_status = WEXITSTATUS(status);
		else
			shell->exit_status = 130;
	}
}
