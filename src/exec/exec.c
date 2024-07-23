/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorvarea <jorvarea@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 16:38:27 by jorvarea          #+#    #+#             */
/*   Updated: 2024/07/23 16:15:00 by jorvarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec(t_shell *shell)
{
	t_cmd	*cmd;

	cmd = shell->tokens;
	init_fds_pid(cmd);
	init_signal_handler_exec();
	while (cmd)
	{
		if (cmd->type == CMD)
			exec_one(shell, cmd);
		cmd = cmd->next;
	}
	wait_pids(shell, shell->tokens);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	init_signal_handler_cli();
}
