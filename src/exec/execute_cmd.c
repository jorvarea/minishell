/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorvarea <jorvarea@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 00:25:52 by jorvarea          #+#    #+#             */
/*   Updated: 2024/07/25 16:53:13 by jorvarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_cmd(t_shell *shell, t_cmd *cmd)
{
	char	**args;

	if (cmd && cmd->args)
	{
		expand_wildcards_cmd(cmd);
		expand_env_cmd(shell, cmd->args);
		args = cmd->args;
		if (args && equal_str(args[0], "echo"))
			echo(shell, args);
		else if (equal_str(args[0], "pwd"))
			pwd(shell, args);
		else if (equal_str(args[0], "env"))
			env(shell, args);
		else if (equal_str(args[0], "cd"))
			cd(shell, args);
		else if (equal_str(args[0], "export"))
			export(shell, args);
		else if (equal_str(args[0], "unset"))
			unset(shell, args);
		else if (equal_str(args[0], "exit"))
			exit_cmd(shell, args);
		else
			execute_bin(shell, args);
	}
}
