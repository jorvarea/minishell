/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorvarea <jorvarea@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 12:30:35 by jorvarea          #+#    #+#             */
/*   Updated: 2024/07/24 18:24:28 by jorvarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	replace_exit_status(t_shell *shell, char **arg, int start_index)
{
	char	*str_replaced;
	char	*exit_status;

	exit_status = ft_itoa(shell->exit_status);
	str_replaced = ft_strrep(*arg, exit_status, start_index,
			start_index + 2);
	free(exit_status);
	if (str_replaced)
	{
		free(*arg);
		*arg = str_replaced;
	}
}

char	*extract_key(char *arg, int start_index, int *end_index)
{
	char	*key;
	int		i;

	i = start_index + 1;
	while (ft_isalnum(arg[i]) || arg[i] == '_')
		i++;
	*end_index = i;
	key = (char *)safe_malloc(*end_index - start_index);
	ft_strlcpy(key, &arg[start_index + 1], *end_index - start_index);
	return (key);
}

void	replace_env(t_shell *shell, char **arg, int start_index)
{
	char	*value;
	char	*key;
	char	*str_replaced;
	int		end_index;

	key = extract_key(*arg, start_index, &end_index);
	value = get_value(shell, key);
	free(key);
	if (value)
	{
		str_replaced = ft_strrep(*arg, value, start_index, end_index);
		free(*arg);
		*arg = str_replaced;
		free(value);
	}
	else
	{
		str_replaced = ft_strrep(*arg, "", start_index, end_index);
		free(*arg);
		*arg = str_replaced;
	}
}

void	replace_home(t_shell *shell, char **arg, int start_index)
{
	char	*home;
	char	*str_replaced;

	home = get_value(shell, "HOME");
	if (home)
	{
		str_replaced = ft_strrep(*arg, home, start_index, start_index + 1);
		if (str_replaced)
		{
			free_array(&arg);
			*arg = str_replaced;
		}
		free(home);
	}
}
