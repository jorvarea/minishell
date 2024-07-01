/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorvarea <jorvarea@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 00:25:52 by jorvarea          #+#    #+#             */
/*   Updated: 2024/07/01 21:09:41 by jorvarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	exec(t_shell *shell, char **args)
{
	bool	exit;

	exit = false;
	shell->exit_status = 0;
	expand_cmd(shell, args);
	if (args && equal_str(args[0], "echo"))
		echo(args);
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
	{
		exit = true;
		exit_cmd(shell, args);
	}
	else
		executable(shell, args);
	return (exit);
}
