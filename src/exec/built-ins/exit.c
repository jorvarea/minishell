/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorvarea <jorvarea@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 23:32:42 by jorvarea          #+#    #+#             */
/*   Updated: 2024/07/16 22:31:16 by jorvarea         ###   ########.fr       */
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

bool	exit_cmd(t_shell *shell, char **args)
{
	bool	exit;

	exit = true;
	shell->exit_status = 0;
	printf("exit\n");
	if (args[1] && ft_isnum(args[1]))
		shell->exit_status = ft_atoi(args[1]) % 256;
	else if (args[1])
	{
		shell->exit_status = 2;
		ft_putstr_fd("-minishell: exit: ", STDERR_FILENO);
		ft_putstr_fd(args[1], STDERR_FILENO);
		ft_putendl_fd(": numeric argument required", STDERR_FILENO);
	}
	if (args[1] && args[2])
	{
		exit = false;
		shell->exit_status = 1;
		ft_putendl_fd("-minishell: exit: too many arguments", STDERR_FILENO);
	}
	return (exit);
}
