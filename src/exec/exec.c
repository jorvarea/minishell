/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorvarea <jorvarea@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 00:25:52 by jorvarea          #+#    #+#             */
/*   Updated: 2024/07/09 18:20:50 by jorvarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	trim_quotes(char **args)
{
	char	*arg_trimmed;
	char	*first_char;
	int		i;

	first_char = (char *)safe_malloc(2);
	i = 0;
	while (args[i])
	{
		first_char[0] = args[i][0];
		first_char[1] = '\0';
		if (first_char[0] == '\'' || first_char[0] == '\"')
		{
			arg_trimmed = ft_strtrim(args[i], first_char);
			free(args[i]);
			args[i] = arg_trimmed;
		}
		i++;
	}
	free(first_char);
}

void	exec(t_shell *shell, t_cmd *cmd)
{
	char	**args;

	expand_wildcards(cmd);
	args = cmd->args;
	expand_cmd(shell, args);
	trim_quotes(args);
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
	else
		execute_bin(shell, args);
}
