/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorvarea <jorvarea@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 00:12:39 by jorvarea          #+#    #+#             */
/*   Updated: 2024/07/24 12:09:57 by jorvarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env(t_shell *shell, char **args)
{
	t_env	*env;

	if (args[1])
	{
		shell->exit_status = 1;
		ft_putendl_fd("env: too many arguments", STDERR_FILENO);
	}
	else
	{
		shell->exit_status = 0;
		env = shell->l_env;
		while (env)
		{
			printf("%s=", env->key);
			printf("%s\n", env->value);
			env = env->next;
		}
	}
}
