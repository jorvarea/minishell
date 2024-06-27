/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorvarea <jorvarea@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 00:12:39 by jorvarea          #+#    #+#             */
/*   Updated: 2024/06/27 00:24:57 by jorvarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env(t_shell *shell, char **args)
{
	t_env	*env;

	shell->exit_status = 0;
	if (args[1])
	{
		shell->exit_status = 1;
		ft_putendl_fd("env: too many arguments", STDERR_FILENO);
	}
	else
	{
		env = shell->l_env;
		while (env)
		{
			printf("%s=%s\n", env->key, env->value);
			env = env->next;
		}
	}
}
