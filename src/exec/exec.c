/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorvarea <jorvarea@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 00:25:52 by jorvarea          #+#    #+#             */
/*   Updated: 2024/06/27 00:31:51 by jorvarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec(t_shell *shell, char **args)
{
	if (args && ft_strncmp(args[0], "echo", ft_strlen("echo")) == 0)
		echo(shell, args);
	else if (ft_strncmp(args[0], "pwd", ft_strlen("pwd")) == 0)
		pwd(shell, args);
	else if (ft_strncmp(args[0], "env", ft_strlen("env")) == 0)
		env(shell, args);
}
