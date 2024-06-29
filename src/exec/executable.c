/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executable.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorvarea <jorvarea@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 21:07:39 by jorvarea          #+#    #+#             */
/*   Updated: 2024/06/30 00:01:14 by jorvarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	find_executable_in_path(t_shell *shell, char **args)
{
	char	path_env[MAX_ENV_SIZE];
	char	**paths;
	char	*full_path;
	char	*path_slash;
	int		i;

	if (get_value(shell, "PATH", path_env, MAX_ENV_SIZE))
	{
		paths = ft_split(path_env, ':');
		i = 0;
		while (paths && paths[i] && errno == ENOENT)
		{
			path_slash = ft_strjoin(paths[i], "/");
			full_path = ft_strjoin(path_slash, args[0]);
			errno = 0;
			execve(full_path, args, shell->env);
			free(path_slash);
			free(full_path);
			i++;
		}
		if (errno == ENOENT)
			ft_command_not_found_error(shell, args[0]);
	}
	else
		ft_minishell_error(shell, "-minishell: PATH not set");
}

void	executable(t_shell *shell, char **args)
{
	update_envp(shell);
	errno = 0;
	execve(args[0], args, shell->env);
	if (errno == ENOENT)
		find_executable_in_path(shell, args);
	else
		ft_perror(shell, "execve", args[0]);
}
