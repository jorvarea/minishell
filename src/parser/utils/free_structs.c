/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 19:21:11 by ana-cast          #+#    #+#             */
/*   Updated: 2024/07/24 12:17:24 by ana-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	free_redir(t_redir	**redir)
{
	t_redir	*next;

	while (*redir)
	{
		next = (*redir)->next;
		if (next)
			next->prev = NULL;
		if ((*redir)->file)
		{
			free((*redir)->file);
			(*redir)->file = NULL;
		}
		if ((*redir)->fd > 0)
			close((*redir)->fd);
		(*redir)->fd = 0;
		free(*redir);
		*redir = NULL;
		*redir = next;
	}
}

void	free_env_list(t_env	**l_env)
{
	t_env	*next;

	while ((*l_env))
	{
		next = (*l_env)->next;
		if (next)
			next->prev = NULL;
		free((*l_env)->key);
		free((*l_env)->value);
		free((*l_env));
		(*l_env) = NULL;
		(*l_env) = next;
	}
}

void	*free_tokens(t_cmd **tokens)
{
	t_cmd	*next;

	while (*tokens)
	{
		next = (*tokens)->next;
		if (next)
			next->prev = NULL;
		free_array(&(*tokens)->args);
		free_redir(&(*tokens)->redir);
		free(*tokens);
		*tokens = NULL;
		*tokens = next;
	}
	return (NULL);
}

void	*free_shell(t_shell **shell)
{
	if ((*shell)->env)
		free_array(&(*shell)->env);
	if ((*shell)->l_env)
		free_env_list(&(*shell)->l_env);
	free(*shell);
	return (NULL);
}
