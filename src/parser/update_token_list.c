/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_token_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 20:46:18 by ana-cast          #+#    #+#             */
/*   Updated: 2024/07/20 22:25:56 by ana-cast         ###   ########.fr       */
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

void	update_redir_token(t_cmd *node)
{
	if (!node || node->type != REDIR)
		return ;
	if (node->redir)
	{
		node->type = CMD;
		free_array(&node->args);
		node->args = (char **)malloc(sizeof(char *) * 1);
		node->args[0] = NULL;
	}
	else
		pop_node_from_list(node);
}

