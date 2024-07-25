/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parenthesis.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorvarea <jorvarea@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 00:31:23 by jorvarea          #+#    #+#             */
/*   Updated: 2024/07/25 01:29:20 by jorvarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	peek_pipes_parenthesis(t_cmd *end)
{
	int	pipes_fd[2];

	if (end->next->next && end->next->next->type == PIPE)
	{
		safe_pipe(pipes_fd);
		end->outfd = pipes_fd[1];
		end->next->next->next->infd = pipes_fd[0];
	}
}

static void	manage_pipes_parenthesis(t_cmd *head, t_cmd *end)
{
	if (head->infd != -1)
	{
		dup2(head->infd, STDIN_FILENO);
		close(head->infd);
	}
	if (end->outfd != -1)
	{
		dup2(end->outfd, STDOUT_FILENO);
		close(end->outfd);
	}
	if (end->next->next && end->next->next->type == PIPE)
		close(end->next->next->next->infd);
}

static void	execute_parenthesis(t_shell *shell, t_cmd *head, t_cmd *end)
{
	peek_pipes_parenthesis(end);
	manage_pipes_parenthesis(head, end);
	exec(shell, head, end);
}

void	manage_parenthesis(t_shell *shell, t_cmd **cmd)
{
	t_cmd	*head;
	t_cmd	*end_node;

	head = *cmd;
	while ((*cmd)->type != CLOSE_PAR)
		*cmd = (*cmd)->next;
	end_node = (*cmd)->prev;
	execute_parenthesis(shell, head, end_node);
}
