/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 21:30:21 by ana-cast          #+#    #+#             */
/*   Updated: 2024/07/24 16:16:28 by ana-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

bool	delete_redir_token(t_shell *shell)
{
	t_cmd	*head;
	t_cmd	*node;
	t_cmd	*next;

	node = shell->tokens;
	head = NULL;
	while (node)
	{
		next = node->next;
		if (node->type == REDIR)
			pop_node_from_list(node);
		else if (!head)
			head = node;
		node = next;
	}
	shell->tokens = head;
	return (0);
}

t_redir	*assign_redir(t_redir *assign, char **args)
{
	t_redir	*new_redir;

	new_redir = (t_redir *)malloc(sizeof(t_redir));
	if (!new_redir)
		return (NULL);
	new_redir->fd = -1;
	new_redir->type = get_redir_type(args[0]);
	new_redir->file = ft_strdup(args[1]);
	new_redir->next = NULL;
	if (!assign)
	{
		new_redir->prev = NULL;
		assign = new_redir;
	}
	else
	{
		new_redir->prev = redir_last_node(assign);
		redir_last_node(assign)->next = new_redir;
	}
	return (assign);
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
}

void	update_redir(t_cmd *redir)
{
	t_cmd	*prev;
	t_cmd	*next;
	t_cmd	*assign;

	prev = redir->prev;
	next = redir->next;
	while (next && next->type == REDIR)
		next = next->next;
	while (prev && prev->type == REDIR)
		prev = prev->prev;
	if (prev && (prev->type == CMD || prev->type == CLOSE_PAR))
		assign = prev;
	else if (next && next->type == CMD)
		assign = next;
	else
		assign = redir;
	assign->redir = assign_redir(assign->redir, redir->args);
	update_redir_token(redir);
}

bool	get_redirs(t_shell *shell)
{
	t_cmd	*node;

	node = shell->tokens;
	while (node)
	{
		if (node->type == REDIR)
		{
			if (check_redir_args(node->args, shell))
				return (1);
			update_redir(node);
		}
		node = node->next;
	}
	return (delete_redir_token(shell));
}
