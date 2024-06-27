/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorvarea <jorvarea@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 00:51:50 by jorvarea          #+#    #+#             */
/*   Updated: 2024/06/27 19:54:07 by jorvarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*expand_home(t_shell *shell, char *path)
{
	char	home[MAX_ENV_SIZE];
	char	*new_path;

	new_path = NULL;
	if (get_value(shell, "HOME", home, sizeof(home)))
		new_path = ft_strjoin(home, path);
	else
		set_and_print_minishell_error(shell, "-minishell: cd: HOME not set");
	return (new_path);
}

// I need to expand the relative paths and the . ..
static void update_pwd_oldpwd(t_shell *shell, char *path)
{
    char pwd[MAX_ENV_SIZE];
    
    if (get_value(shell, "PWD", pwd, MAX_ENV_SIZE))
    {
        update_env(shell, "OLDPWD", pwd);
        if (!update_env(shell, "PWD", path))
		    add_new_env(shell, "PWD", path);
    }
    else
        set_and_print_minishell_error(shell, "-minishell: cd: PWD not set");
}

static void	change_directory(t_shell *shell, char *path)
{
	if (chdir(path) == 0)
		update_pwd_oldpwd(shell, path);
	else
		set_and_print_perror(shell, "chdir");
}

static void	process_cd_args(t_shell *shell, char **args)
{
	char	*path;

	if (!args[1])
		take_me_home(shell);
	else if (args[1] && args[1][0] == '-' && args[1][1] == '\0')
		take_me_back(shell);
	else if (args[1] && args[1][0] == '~')
	{
		path = expand_home(shell, &args[1][1]);
		if (path)
			change_directory(shell, path);
	}
	else
		change_directory(shell, args[1]);
}

void	cd(t_shell *shell, char **args)
{
	shell->exit_status = 0;
	if (found_flags(args))
	{
		shell->exit_status = 1;
		print_invalid_flag_error_msg("pwd", args[1][1], "pwd");
	}
	else if (count_words(args) > 2)
		set_and_print_minishell_error(shell,
			"-minishell: cd: too many arguments");
	else
		process_cd_args(shell, args);
}
