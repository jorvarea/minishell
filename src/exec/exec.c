/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorvarea <jorvarea@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 16:38:27 by jorvarea          #+#    #+#             */
/*   Updated: 2024/07/16 13:05:39 by jorvarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec(t_shell *shell, t_cmd *cmd)
{
	while (cmd)
	{
		if (cmd->type == CMD)
			execute_redir(shell, cmd);
		cmd = cmd->next;
	}
}
