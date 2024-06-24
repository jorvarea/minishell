/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 19:21:11 by ana-cast          #+#    #+#             */
/*   Updated: 2024/06/24 16:38:06 by ana-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	free_commands(t_cmd *command_lst)
{
	t_cmd	*next;

	while (command_lst)
	{
		next = command_lst->next;
		sh_free_str(command_lst->cmd);
		free_array(command_lst->args);
		free_arg_lst(command_lst->l_args);
		free_redir(command_lst->redir);
		free(command_lst);
		command_lst = NULL;
		command_lst = next;
		command_lst->prev = NULL;
	}
}

void	free_shell(t_shell *shell)
{
	if (shell->env)
		free_array(shell->env);
	if (shell->tokens)
		free_commands(shell->tokens);
	if (shell->l_env)
		free_env_list(shell->l_env);
	if (shell->files)
		free_arg_lst(shell->files);
	free(shell);
	printf("%sSuccesfully freed shell%s\n", GREEN, WHITE);
}
