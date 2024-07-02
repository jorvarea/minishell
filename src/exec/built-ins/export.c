/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorvarea <jorvarea@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 11:55:01 by jorvarea          #+#    #+#             */
/*   Updated: 2024/07/02 19:06:20 by jorvarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	extract_key_value(char *arg, char **key, char **value)
{
	int	i;

	i = 0;
	while (arg[i] && arg[i] != '=')
		i++;
	*key = (char *)safe_malloc(i + 1);
	*value = (char *)safe_malloc(ft_strlen(&arg[i + 1]) + 1);
	ft_strlcpy(*key, arg, i + 1);
	ft_strlcpy(*value, &arg[i + 1], ft_strlen(&arg[i + 1]) + 1);
	if (!valid_key(*key) || i == ft_strlen(arg))
	{
		free(*key);
		*key = NULL;
		free(*value);
		*value = NULL;
	}
}

static void	process_export_args(t_shell *shell, char **args)
{
	char	*key;
	char	*value;
	int		i;

	i = 1;
	while (args[i])
	{
		extract_key_value(args[i], &key, &value);
		if (key && value)
		{
			if (!update_env(shell, key, value))
				add_new_env(shell, key, value);
			free(key);
			free(value);
		}
		else
		{
			shell->exit_status = 1;
			ft_putstr_fd("-minishell: export: `", STDERR_FILENO);
			ft_putstr_fd(args[i], STDERR_FILENO);
			ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
		}
		i++;
	}
}

static void	show_exported_variables(t_shell *shell)
{
	t_env	*env;

	env = shell->l_env;
	while (env)
	{
		printf("declare -x %s=\"%s\"\n", env->key, env->value);
		env = env->next;
	}
}

void	export(t_shell *shell, char **args)
{
	shell->exit_status = 0;
	if (found_flags(args))
		ft_invalid_flag_error(shell, "export", args[1][1],
			"export [name=value ...]");
	else
	{
		if (count_words(args) == 1)
			show_exported_variables(shell);
		else
			process_export_args(shell, args);
	}
}
