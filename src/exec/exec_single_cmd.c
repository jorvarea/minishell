/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_single_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorvarea <jorvarea@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 15:14:47 by jorvarea          #+#    #+#             */
/*   Updated: 2024/07/23 15:16:58 by jorvarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_single_cmd(t_shell *shell)
{
	pid_t	pid;
	int		status;

	pid = safe_fork();
	if (pid == 0)
	{
		execute_redir(shell, shell->tokens);
		exit(shell->exit_status);
	}
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			shell->exit_status = WEXITSTATUS(status);
		else
			shell->exit_status = 130;
		close(STDIN_FILENO);
		close(STDOUT_FILENO);
	}
}
