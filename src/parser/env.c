/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 18:12:12 by ana-cast          #+#    #+#             */
/*   Updated: 2024/07/16 19:48:55 by ana-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	**init_shell_env(char **envp)
{
	char	**env;
	int		len;

	len = 0;
	if (envp)
	{
		while (envp[len])
			len++;
		env = (char **)safe_malloc(sizeof(char *) * (len + 1));
		if (!env)
			return (NULL);
		len = -1;
		while (envp[++len])
			env[len] = ft_strdup(envp[len]);
		env[len] = NULL;
	}
	else
		env = NULL;
	return (env);
}

t_env	*assign_env_values(char *env, t_env *new_env)
{
	char	**env_split;

	env_split = ft_split(env, '=');
	if (!env_split)
		return (NULL);
	new_env->key = ft_strdup(env_split[0]);
	if (env_split[1])
		new_env->value = ft_strdup(env_split[1]);
	else
		new_env->value = ft_strdup("\0");
	free_array(&env_split);
	return (new_env);
}

t_env	*set_env_list(char **env)
{
	int		i;
	t_env	*l_env;
	t_env	*new_env;

	i = -1;
	l_env = NULL;
	while (env[++i])
	{
		new_env = (t_env *)safe_malloc(sizeof(t_env));
		if (!new_env)
			return (NULL);
		new_env = assign_env_values(env[i], new_env);
		new_env->next = NULL;
		if (!l_env)
		{
			new_env->prev = NULL;
			l_env = new_env;
		}
		else
		{
			new_env->prev = env_last_node(l_env);
			env_last_node(l_env)->next = new_env;
		}
	}
	return (l_env);
}
