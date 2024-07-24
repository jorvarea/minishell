/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 23:32:42 by jorvarea          #+#    #+#             */
/*   Updated: 2024/07/24 13:40:45 by ana-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	ft_isnum(char *str)
{
	bool	is_num;
	int		i;

	is_num = true;
	i = 0;
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			is_num = false;
		i++;
	}
	return (is_num);
}

void	exit_shell(t_shell *shell)
{
	int	status;

	status = shell->exit_status;
	printf("exit\n");
	if (shell->tokens)
		free_tokens(&shell->tokens);
	free_shell(&shell);
	exit(status);
}

void	exit_cmd(t_shell *shell, char **args)
{
	bool	exit;

	exit = true;
	shell->exit_status = 0;
	if (args[1] && ft_isnum(args[1]))
	{
		if (args[2])
		{
			exit = false;
			shell->exit_status = 1;
			ft_putendl_fd("minishell: exit: too many arguments", STDERR_FILENO);
		}
		else
			shell->exit_status = ft_atoi(args[1]) % 256;
	}
	else if (args[1])
	{
		shell->exit_status = 2;
		ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
		ft_putstr_fd(args[1], STDERR_FILENO);
		ft_putendl_fd(": numeric argument required", STDERR_FILENO);
	}
	if (exit)
		exit_shell(shell);
}
