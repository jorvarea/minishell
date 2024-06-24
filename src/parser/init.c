/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 17:44:05 by ana-cast          #+#    #+#             */
/*   Updated: 2024/06/24 18:12:31 by ana-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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
	shell->l_env = set_env_list(shell->env);
	shell->files = NULL;
	return (shell);
}
