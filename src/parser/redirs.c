/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 21:30:21 by ana-cast          #+#    #+#             */
/*   Updated: 2024/07/20 23:02:02 by ana-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

bool	check_redir_args(char **redir, t_shell *shell)
{
	if (array_len(redir) != 2 || !redir[0] || get_redir_type(redir[0]) < 0)
		ft_redir_error(redir[0], shell);
	else if (!redir[1] || get_token_type(redir + 1) != CMD)
		ft_redir_error(redir[1], shell);
	else
		return (0);
	return (1);
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

void	update_redir(t_cmd *redir, t_shell *shell)
{
	t_cmd	*prev;
	t_cmd	*next;
	t_cmd	*assign;

	if (check_redir_args(redir->args, shell))
		return ;
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

void	get_redirs(t_shell *shell)
{
	t_cmd	*node;

	node = shell->tokens;
	while (node)
	{
		if (node->type == REDIR)
			update_redir(node, shell);
		node = node->next;
	}
}
