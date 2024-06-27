/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorvarea <jorvarea@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 11:40:24 by jorvarea          #+#    #+#             */
/*   Updated: 2024/06/27 22:44:13 by jorvarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pwd(t_shell *shell, char **args)
{
	char	cwd[MAX_ENV_SIZE];

	shell->exit_status = 0;
	if (found_flags(args))
		set_and_print_invalid_flag_error(shell, "pwd", args[1][1], "pwd");
	else
	{
		if (getcwd(cwd, sizeof(cwd)))
			ft_putendl_fd(cwd, STDOUT_FILENO);
		else
		{
			shell->exit_status = 1;
			perror("getcwd");
		}
	}
}
