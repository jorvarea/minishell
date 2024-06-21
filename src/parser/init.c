/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 17:44:05 by ana-cast          #+#    #+#             */
/*   Updated: 2024/06/21 13:43:27 by ana-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	**init_shell_env(char **envp)
{
	char	**env;
	int		len;

	len = 0;
	while (envp[len])
		len++;
	env = (char **)malloc(sizeof(char *) * len + 1);
	if (!env)
		return (NULL);
	len = -1;
	while (envp[++len])
		env[len] = ft_strdup(envp[len]);
	env[len] = NULL;
	return (env);
}

/*
TO-DO:
 - (void)envp: Eliminar cuando haya hecho la copia de envp en shell->env
 - shell->env = NULL: Puesto mientras no programe la asignacion/copia
*/
t_shell *init_shell(char **envp)
{
	t_shell	*shell;

	shell = (t_shell *)malloc(sizeof(t_shell));
	if (!shell)
		exit_program_nl();
	shell->env = init_shell_env(envp);
	shell->exit_status = 0;
	return (shell);
}

t_cmd	init_command(void);