/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_redir_token.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 13:49:17 by ana-cast          #+#    #+#             */
/*   Updated: 2024/07/24 15:49:01 by ana-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

bool	delete_redir_token(t_shell *shell)
{
	t_cmd	*head;
	t_cmd	*node;
	t_cmd	*next;

	head = NULL;
	node = shell->tokens;
	while (node)
	{
		next = node->next;
		if (node->type == REDIR)
		{
			if (node->next)
				node->next->prev = node->prev;
			if (node->prev)
				node->prev->next = node->next;
			node->prev = NULL;
			node->next = NULL;
			free_array(&node->args);
			free(node);
			node = NULL;
		}
		else if (!head)
			head = node;
		node = next;
	}
	shell->tokens = head;
	return (0);
}
