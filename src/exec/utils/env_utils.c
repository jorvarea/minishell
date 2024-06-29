/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorvarea <jorvarea@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 22:39:34 by jorvarea          #+#    #+#             */
/*   Updated: 2024/06/28 01:59:02 by jorvarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	get_value(t_shell *shell, char *key, char *value, int value_size)
{
	t_env	*ptr;
	bool	found;

	found = false;
	ptr = shell->l_env;
	while (!found && ptr)
	{
		if (equal_str(ptr->key, key))
		{
			found = true;
			if (ptr->value)
				ft_strlcpy(value, ptr->value, value_size);
			else
				value = NULL;
		}
		ptr = ptr->next;
	}
	return (found);
}

bool	remove_key(t_shell *shell, char *key)
{
	t_env	*ptr;
	bool	found;

	found = false;
	ptr = shell->l_env;
	while (!found && ptr)
	{
		if (equal_str(ptr->key, key))
		{
			found = true;
			if (ptr->prev)
				ptr->prev->next = ptr->next;
			else
				shell->l_env = ptr->next;
			if (ptr->next)
				ptr->next->prev = ptr->prev;
			free(ptr->key);
			if (ptr->value)
				free(ptr->value);
			free(ptr);
		}
		else
			ptr = ptr->next;
	}
	return (found);
}

void	add_new_env(t_shell *shell, char *key, char *value)
{
	t_env	*env;
	t_env	*last_env;

	env = (t_env *)malloc(sizeof(t_env));
	env->key = ft_strdup(key);
	if (value)
		env->value = ft_strdup(value);
	else
		env->value = NULL;
	last_env = find_last_env(shell->l_env);
	env->prev = last_env;
	last_env->next = env;
	env->next = NULL;
}

bool	valid_key_value(char **key_value)
{
	bool	valid;
	int		i;

	valid = false;
	if (key_value && key_value[0])
	{
		valid = ft_isalpha(key_value[0][0]) || key_value[0][0] == '_';
		i = 1;
		while (valid && key_value[0][i])
		{
			if (!ft_isalnum(key_value[0][i]) && key_value[0][i] != '_')
				valid = false;
			i++;
		}
	}
	return (valid);
}

bool	update_env(t_shell *shell, char *key, char *value)
{
	t_env	*ptr;
	bool	found;

	found = false;
	ptr = shell->l_env;
	while (!found && ptr)
	{
		if (equal_str(ptr->key, key))
		{
			found = true;
			if (ptr->value)
				free(ptr->value);
			ptr->value = ft_strdup(value);
		}
		ptr = ptr->next;
	}
	return (found);
}
