/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorvarea <jorvarea@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 16:38:27 by jorvarea          #+#    #+#             */
/*   Updated: 2024/07/22 23:41:50 by jorvarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec(t_shell *shell)
{
	t_cmd	*cmd;
	int		bk_in;
	int		bk_out;

	bk_in = dup(STDIN_FILENO);
	bk_out = dup(STDOUT_FILENO);
	cmd = shell->tokens;
	init_fds_pid(cmd);
	assign_pipes(cmd);
	while (cmd)
	{
		if (cmd->type == CMD)
			exec_one(shell, cmd);
		cmd = cmd->next;
	}
	dup2(bk_in, STDIN_FILENO);
	dup2(bk_out, STDOUT_FILENO);
	close(bk_in);
	close(bk_out);
	wait_pids(shell, shell->tokens);
}
