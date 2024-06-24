/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 17:44:05 by ana-cast          #+#    #+#             */
/*   Updated: 2024/06/24 16:37:16 by ana-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	**init_shell_env(char **envp)
{
	char	**env;
	int		len;

	len = 0;
	if (envp)
	{
		while (envp[len])
			len++;
		env = (char **)malloc(sizeof(char *) * (len + 1));
		if (!env)
			return (NULL);
		len = -1;
		while (envp[++len])
			env[len] = ft_strdup(envp[len]);
		env[len] = NULL;
	}
	else
		env = NULL;
	return (env);
}

t_cmd	*init_command(void)
{
	t_cmd	*tokens;

	tokens = (t_cmd *)malloc(sizeof(t_cmd));
	return (tokens);
}

t_shell	*init_shell(char **envp)
{
	t_shell	*shell;

	shell = (t_shell *)malloc(sizeof(t_shell));
	if (!shell)
		exit_program_nl();
	shell->env = init_shell_env(envp);
	shell->exit_status = 0;
	shell->tokens = NULL;
	shell->l_env = NULL;
	shell->files = NULL;
	return (shell);
}
