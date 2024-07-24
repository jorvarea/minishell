/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_envp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorvarea <jorvarea@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 21:13:24 by jorvarea          #+#    #+#             */
/*   Updated: 2024/07/24 18:16:07 by jorvarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_envp(t_shell *shell)
{
	t_env	*env;
	int		count;

	env = shell->l_env;
	count = 0;
	while (env)
	{
		count++;
		env = env->next;
	}
	return (count);
}

void	update_envp(t_shell *shell)
{
	t_env	*env;
	char	*key_equal;
	int		i;

	free_array(&shell->env);
	shell->env = (char **)safe_malloc((count_envp(shell) + 1) * sizeof(char *));
	env = shell->l_env;
	i = 0;
	while (env)
	{
		key_equal = ft_strjoin(env->key, "=");
		if (env->value)
		{
			shell->env[i] = ft_strjoin(key_equal, env->value);
			free(key_equal);
		}
		else
			shell->env[i] = key_equal;
		env = env->next;
		i++;
	}
	shell->env[i] = NULL;
}
