/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 17:44:05 by ana-cast          #+#    #+#             */
/*   Updated: 2024/06/19 19:42:15 by ana-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*
TO-DO:
 - (void)envp: Eliminar cuando haya hecho la copia de envp en shell->env
 - shell->env = NULL: Puesto mientras no programe la asignacion/copia
*/
t_shell *init_shell(char **envp)
{
	t_shell	*shell;

	(void)envp; // Change when finish assigning shell->env to envp
	shell = (t_shell *)malloc(sizeof(t_shell));
	if (!shell)
		exit_program_nl();
	shell->env = NULL; // copy envp to env (use malloc 4 env + strdup 4 env[i])
	shell->exit_status = 0;
	return (shell);
}

t_cmd	init_command(void);