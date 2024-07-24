/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_nodes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 19:48:16 by ana-cast          #+#    #+#             */
/*   Updated: 2024/07/24 15:28:04 by ana-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	pop_node_from_list(t_cmd *node)
{
	t_cmd	*prev;
	t_cmd	*next;

	prev = node->prev;
	next = node->next;
	if (next)
		next->prev = prev;
	if (prev)
		prev->next = next;
	free_array(&node->args);
	free(node);
	node = NULL;
}

t_cmd	*token_last_node(t_cmd *list)
{
	if (!list)
		return (NULL);
	while (list->next)
		list = list->next;
	return (list);
}

t_env	*env_last_node(t_env *l_env)
{
	if (!l_env)
		return (NULL);
	while (l_env->next)
		l_env = l_env->next;
	return (l_env);
}

t_redir	*redir_last_node(t_redir *redir)
{
	if (!redir)
		return (NULL);
	while (redir->next)
		redir = redir->next;
	return (redir);
}
