/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorvarea <jorvarea@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 12:30:35 by jorvarea          #+#    #+#             */
/*   Updated: 2024/07/01 21:11:27 by jorvarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	replace_wildcard(t_shell *shell, char **arg, int start_index)
{
	start_index = start_index;
}

void	replace_env(t_shell *shell, char **arg, int start_index)
{
	start_index = start_index;
}

void	replace_home(t_shell *shell, char **arg, int start_index)
{
	char	home[MAX_ENV_SIZE];
	char	*str_replaced;

	if (get_value(shell, "HOME", home, MAX_ENV_SIZE))
	{
		str_replaced = ft_strrep(*arg, home, start_index, 1);
		if (str_replaced)
		{
			free(*arg);
			*arg = str_replaced;
		}
	}
}
