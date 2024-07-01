/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorvarea <jorvarea@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 00:51:50 by jorvarea          #+#    #+#             */
/*   Updated: 2024/07/01 22:09:38 by jorvarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	take_me_home(t_shell *shell)
{
	char	home[MAX_ENV_SIZE];

	if (get_value(shell, "HOME", home, MAX_ENV_SIZE))
		change_directory(shell, home);
	else
		ft_minishell_error(shell, "-minishell: cd: HOME not set");
}

static void	take_me_back(t_shell *shell)
{
	char	oldpwd[MAX_ENV_SIZE];
	char	pwd[MAX_ENV_SIZE];

	if (get_value(shell, "OLDPWD", oldpwd, MAX_ENV_SIZE))
	{
		change_directory(shell, oldpwd);
		if (getcwd(pwd, MAX_ENV_SIZE))
			ft_putendl_fd(pwd, STDOUT_FILENO);
		else
			ft_perror(shell, "getcwd", "");
	}
	else
		ft_minishell_error(shell, "-minishell: cd: OLDPWD not set");
}

static void	process_cd_args(t_shell *shell, char **args)
{
	if (!args[1])
		take_me_home(shell);
	else if (args[1] && args[1][0] == '-' && args[1][1] == '\0')
		take_me_back(shell);
	else
		change_directory(shell, args[1]);
}

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

void	cd(t_shell *shell, char **args)
{
	if (found_flags(args))
		ft_invalid_flag_error(shell, "cd", args[1][1], "cd [dir]");
	else if (count_words(args) > 2)
		ft_minishell_error(shell,
			"-minishell: cd: too many arguments");
	else
		process_cd_args(shell, args);
}
