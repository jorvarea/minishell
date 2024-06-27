/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorvarea <jorvarea@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 00:51:50 by jorvarea          #+#    #+#             */
/*   Updated: 2024/06/27 15:50:38 by jorvarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Necesito nueva funcion en env_utils para cambiar el valor de una variable)
void	cd(t_shell *shell, char **args)
{
	char	value[MAX_ENV_SIZE];
	t_env	*env;

	shell->exit_status = 0;
	if (!args[1] || (args[1] && ft_strncmp(args[1], "~", 1) == 0))
	{
		get_value(shell, "HOME", value, sizeof(value));
		chdir(value);
	}
	else
	{
		printf("aqui estoy");
	}
}
