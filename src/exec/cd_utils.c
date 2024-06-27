/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorvarea <jorvarea@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 19:14:15 by jorvarea          #+#    #+#             */
/*   Updated: 2024/06/27 19:23:14 by jorvarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	take_me_home(t_shell *shell)
{
	char	home[MAX_ENV_SIZE];

	if (get_value(shell, "HOME", home, MAX_ENV_SIZE))
	{
		if (chdir(home) == 0)
		{
			if (!update_env(shell, "PWD", home))
				add_new_env(shell, "PWD", home);
		}
		else
			set_and_print_perror(shell, "chdir");
	}
	else
		set_and_print_minishell_error(shell, "-minishell: cd: HOME not set");
}

void	take_me_back(t_shell *shell)
{
	char	pwd[MAX_ENV_SIZE];
	char	oldpwd[MAX_ENV_SIZE];

	if (get_value(shell, "OLDPWD", oldpwd, MAX_ENV_SIZE))
	{
		if (get_value(shell, "PWD", pwd, MAX_ENV_SIZE))
		{
			if (chdir(oldpwd) == 0)
			{
				update_env(shell, "OLDPWD", pwd);
				update_env(shell, "PWD", oldpwd);
				ft_putendl_fd(pwd, STDOUT_FILENO);
			}
			else
				set_and_print_perror(shell, "chdir");
		}
		else
			set_and_print_minishell_error(shell, "-minishell: cd: PWD not set");
	}
	else
		set_and_print_minishell_error(shell, "-minishell: cd: OLDPWD not set");
}
