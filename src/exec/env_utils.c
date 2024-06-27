/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorvarea <jorvarea@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 22:39:34 by jorvarea          #+#    #+#             */
/*   Updated: 2024/06/27 15:16:47 by jorvarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	get_value(t_shell *shell, char *key, char *value, int value_size)
{
	t_env	*ptr;
	bool	found;

	found = false;
	ptr = shell->l_env;
	while (ptr && ptr->next)
	{
		if (ft_strncmp(ptr->key, key, ft_strlen(key)) == 0
			&& ft_strlen(ptr->value) < value_size)
		{
			found = true;
			ft_strlcpy(value, ptr->value, value_size);
		}
		ptr = ptr->next;
	}
	return (found);
}

void	add_new_env(t_shell *shell, char *key, char *value)
{
	t_env	*env;

	env = (t_env *)malloc(sizeof(t_env));
	env->key = ft_strdup(key);
	env->value = ft_strdup(value);
	env_last_node(shell->l_env)->next = env;
	env->prev = env_last_node(shell->l_env);
	env->next = NULL;
}

bool	valid_key_value(char **key_value)
{
	bool	valid;
	int		i;

	valid = ft_isalpha(key_value[0][0]) || key_value[0][0] == '_';
	i = 1;
	while (valid && key_value[0][i])
	{
		if (!ft_isalnum(key_value[0][i]) && key_value[0][i] != '_')
			valid = false;
		i++;
	}
	return (valid);
}
