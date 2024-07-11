/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorvarea <jorvarea@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 16:38:27 by jorvarea          #+#    #+#             */
/*   Updated: 2024/07/11 22:46:20 by jorvarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec(t_shell *shell, t_cmd *cmd)
{
	pid_t	pid;
	int		status;

	while (cmd)
	{
		if (cmd->type == CMD)
		{
			pid = fork();
			if (pid < 0)
			{
				ft_perror(shell, "fork", "");
				exit(EXIT_FAILURE);
			}
			else if (pid == 0)
			{
				execute_cmd(shell, cmd);
				exit(0);
			}
			else
				waitpid(pid, &status, 0);
		}
		cmd = cmd->next;
	}
}
