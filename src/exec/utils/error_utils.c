/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorvarea <jorvarea@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 18:22:55 by jorvarea          #+#    #+#             */
/*   Updated: 2024/06/30 12:40:37 by jorvarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_minishell_error(t_shell *shell, char *msg)
{
	shell->exit_status = 1;
	ft_putendl_fd(msg, STDERR_FILENO);
}

void	ft_perror(t_shell *shell, char *function, char *arg)
{
	shell->exit_status = 1;
	ft_putstr_fd("-minishell: ", STDERR_FILENO);
	ft_putstr_fd(function, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	perror("");
}

void	ft_invalid_flag_error(t_shell *shell, char *cmd,
		char invalid_flag, char *usage)
{
	shell->exit_status = 2;
	ft_putstr_fd("-minishell: ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": -", STDERR_FILENO);
	ft_putchar_fd(invalid_flag, STDERR_FILENO);
	ft_putendl_fd(": invalid option", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": usage: ", STDERR_FILENO);
	ft_putendl_fd(usage, STDERR_FILENO);
}

void	ft_command_not_found_error(t_shell *shell, char *cmd)
{
	shell->exit_status = 127;
	ft_putstr_fd("-minishell: ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd("command not found", STDERR_FILENO);
}
