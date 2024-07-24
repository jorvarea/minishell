/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_token_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 19:57:45 by ana-cast          #+#    #+#             */
/*   Updated: 2024/07/24 12:31:30 by ana-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	join_redirs(t_redir *redir1, t_redir *redir2)
{
	if (!redir1)
		redir1 = redir2;
	else if (!redir2)
		;
	else
	{
		redir2->prev = redir_last_node(redir1);
		redir_last_node(redir1)->next = redir2;
	}
}

char	**join_args(char **args1, char **args2)
{
	int		len_arg1;
	int		len_arg2;
	int		i;
	char	**join;

	len_arg1 = array_len(args1);
	len_arg2 = array_len(args2);
	i = len_arg1 + len_arg2;
	join = (char **)malloc(sizeof(char *) * (i + 1));
	if (!join)
		return (NULL);
	i = -1;
	while (++i < len_arg1)
		join[i] = ft_strdup(args1[i]);
	i = -1;
	while (++i < len_arg2)
		join[i + len_arg1] = ft_strdup(args2[i]);
	join[i + len_arg1] = NULL;
	free_array(&args1);
	return (join);
}

bool	join_tokens(t_cmd **node)
{
	int	len;

	len = array_len((*node)->args) + array_len((*node)->next->args);
	(*node)->args = join_args((*node)->args, (*node)->next->args);
	if (!(*node)->args)
		return (1);
	if (!(*node)->redir)
		(*node)->redir = (*node)->next->redir;
	else if (!(*node)->next->redir)
		;
	else
	{
		(*node)->next->redir->prev = redir_last_node((*node)->redir);
		redir_last_node((*node)->redir)->next = (*node)->next->redir;
	}
	pop_node_from_list((*node)->next);
	return (0);
}

/*
 - unir comandos
 - quitar comillas de comando + expansion variables
*/
bool	update_token_list(t_shell *shell)
{
	t_cmd	*node;
	int		i;

	i = 0;
	node = shell->tokens;
	while (node && ++i)
	{
		if (node->type == CMD)
		{
			while (node->next && node->next->type == CMD)
				join_tokens(&node);
		}
		node = node->next;
	}
	return (0);
}
