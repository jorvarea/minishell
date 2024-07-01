/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorvarea <jorvarea@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 00:25:52 by jorvarea          #+#    #+#             */
/*   Updated: 2024/07/01 23:51:22 by jorvarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	trim_quotes(char **args)
{
	char	*arg_trimmed;
	int		i;

	i = 0;
	while (args[i])
	{
		arg_trimmed = ft_strtrim(args[i], "\"\'");
		free(args[i]);
		args[i] = arg_trimmed;
		i++;
	}
}

void	exec(t_shell *shell, char **args)
{
	shell->exit_status = 0;
	expand_cmd(shell, args);
	trim_quotes(args);
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
	else
		execute_bin(shell, args);
}
