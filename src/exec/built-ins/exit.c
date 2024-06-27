/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorvarea <jorvarea@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 23:32:42 by jorvarea          #+#    #+#             */
/*   Updated: 2024/06/27 23:41:34 by jorvarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_cmd(t_shell *shell, char **args)
{
	shell->exit_status = 0;
	if (args[1])
	{
		shell->exit_status = 1;
		ft_putendl_fd("-minishell: exit: too many arguments", STDERR_FILENO);
	}
}
