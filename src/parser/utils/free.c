/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 19:21:11 by ana-cast          #+#    #+#             */
/*   Updated: 2024/07/16 17:02:15 by ana-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	free_commands(t_cmd *command_lst)
{
	t_cmd	*next;

	next = (t_cmd *)malloc(sizeof(t_cmd));
	while (command_lst)
	{
		next = command_lst->next;
		if (next)
			next->prev = NULL;
		free(command_lst->cmd);
		free_array(&command_lst->args);
		free_redir(command_lst->redir);
		free(command_lst);
		command_lst = NULL;
		command_lst = next;
	}
	free(next);
}

void	free_shell(t_shell *shell)
{
	if (shell->env)
		free_array(&shell->env);
	if (shell->l_env)
		free_env_list(shell->l_env);
	if (shell->files)
		free_arg_lst(shell->files);
	free(shell);
	printf("\n%sSuccesfully freed shell%s\n", GREEN, WHITE);
}
