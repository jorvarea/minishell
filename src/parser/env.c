/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 18:12:12 by ana-cast          #+#    #+#             */
/*   Updated: 2024/06/24 18:12:37 by ana-cast         ###   ########.fr       */
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
		env = (char **)malloc(sizeof(char *) * (len + 1));
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

t_env	*env_last_node(t_env *l_env)
{
	if (!l_env)
		return (NULL);
	while (l_env->next)
		l_env = l_env->next;
	return (l_env);
}

t_env	*assign_env_values(char *env, t_env *new_env)
{
	int		i;
	char	**env_split;

	i = 0;
	env_split = ft_split(env, '=');
	new_env->key = ft_strdup(env_split[0]);
	if (env_split[1])
		new_env->value = ft_strdup(env_split[1]);
	else
		new_env->value = NULL;
	free_array(env_split);
	return (new_env);
}

t_env	*set_env_list(char **env)
{
	int		i;
	t_env	*l_env;
	t_env	*new_env;

	i = 0;
	l_env = NULL;
	while (env[i])
	{
		new_env = (t_env *)malloc(sizeof(t_env));
		new_env = assign_env_values(env[i], new_env);
		new_env->next = NULL;
		if (!l_env)
		{
			new_env->prev = NULL;
			l_env = new_env;
		}
		else
		{
			env_last_node(l_env)->next = new_env;
			new_env->prev = env_last_node(l_env);
		}
		i++;
	}
	return (l_env);
}
