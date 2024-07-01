/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorvarea <jorvarea@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 22:39:34 by jorvarea          #+#    #+#             */
/*   Updated: 2024/07/01 23:58:52 by jorvarea         ###   ########.fr       */
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
				value[0] = '\0';
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

bool	valid_key(char *key)
{
	bool	valid;
	int		i;

	valid = false;
	if (key)
	{
		valid = ft_isalpha(key[0]) || key[0] == '_';
		i = 1;
		while (valid && key[i])
		{
			if (!ft_isalnum(key[i]) && key[i] != '_')
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
