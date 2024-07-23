/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorvarea <jorvarea@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 16:38:27 by jorvarea          #+#    #+#             */
/*   Updated: 2024/07/23 17:48:11 by jorvarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec(t_shell *shell)
{
	t_cmd	*cmd;

	cmd = shell->tokens;
	init_fds_pid(cmd);
	while (cmd)
	{
		if (cmd->type == CMD)
			exec_one(shell, cmd);
		cmd = cmd->next;
	}
	wait_pids(shell, shell->tokens);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
}
