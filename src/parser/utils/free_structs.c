/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 19:21:11 by ana-cast          #+#    #+#             */
/*   Updated: 2024/07/22 22:01:32 by ana-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	free_redir(t_redir	*redir)
{
	t_redir	*next;

	while (redir)
	{
		next = redir->next;
		if (next)
			next->prev = NULL;
		free(redir->file);
		if (redir->fd > 0)
			close(redir->fd);
		redir->fd = 0;
		free(redir);
		redir = NULL;
		redir = next;
	}
}

void	free_env_list(t_env	*l_env)
{
	t_env	*next;

	while (l_env)
	{
		next = l_env->next;
		if (next)
			next->prev = NULL;
		free(l_env->key);
		free(l_env->value);
		free(l_env);
		l_env = NULL;
		l_env = next;
	}
}

void	*free_commands(t_cmd **command_lst)
{
	t_cmd	*next;

	next = (t_cmd *)malloc(sizeof(t_cmd));
	while (*command_lst)
	{
		next = (*command_lst)->next;
		if (next)
			next->prev = NULL;
		free_array(&(*command_lst)->args);
		free_redir((*command_lst)->redir);
		free(*command_lst);
		*command_lst = NULL;
		*command_lst = next;
	}
	free(next);
	return (NULL);
}

void	free_shell(t_shell *shell)
{
	if (shell->env)
		free_array(&shell->env);
	if (shell->l_env)
		free_env_list(shell->l_env);
	free(shell);
}
