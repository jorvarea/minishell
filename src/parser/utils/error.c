/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 20:22:04 by ana-cast          #+#    #+#             */
/*   Updated: 2024/07/20 20:27:58 by ana-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_quotes_error(const char *cmd, t_shell *shell)
{
	shell->exit_status = 127;
	ft_putstr_fd("-minishell: ", STDERR_FILENO);
	ft_putstr_fd((char *)cmd, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd("unclosed quotes", STDERR_FILENO);
}

void	ft_redir_error(char *str, t_shell *shell)
{
	shell->exit_status = 127;
	ft_putstr_fd("\n-minishell: ", STDERR_FILENO);
	ft_putstr_fd("syntax error near redirection `", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putendl_fd("\'", STDERR_FILENO);
}
