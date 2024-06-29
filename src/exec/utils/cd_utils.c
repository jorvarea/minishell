/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorvarea <jorvarea@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 19:14:15 by jorvarea          #+#    #+#             */
/*   Updated: 2024/06/30 00:02:47 by jorvarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	change_directory(t_shell *shell, char *path)
{
	char	pwd[MAX_ENV_SIZE];
	char	oldpwd[MAX_ENV_SIZE];

	if (getcwd(oldpwd, MAX_ENV_SIZE))
	{
		if (chdir(path) == 0)
		{
			if (getcwd(pwd, MAX_ENV_SIZE))
			{
				if (!update_env(shell, "OLDPWD", oldpwd))
					add_new_env(shell, "OLDPWD", oldpwd);
				if (!update_env(shell, "PWD", pwd))
					add_new_env(shell, "PWD", pwd);
			}
			else
				ft_perror(shell, "getcwd", "");
		}
		else
			ft_perror(shell, "chdir", path);
	}
	else
		ft_perror(shell, "getcwd", "");
}
