/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parenthesis.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorvarea <jorvarea@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 00:31:23 by jorvarea          #+#    #+#             */
/*   Updated: 2024/07/25 16:10:57 by jorvarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	peek_pipes_parenthesis(t_cmd *end)
{
	int	pipes_fd[2];

	if (end->next && end->next->type == PIPE)
	{
		safe_pipe(pipes_fd);
		end->outfd = pipes_fd[1];
		end->next->next->infd = pipes_fd[0];
	}
}

static void	manage_pipes_parenthesis(t_cmd *head, t_cmd *end)
{
	if (head->prev->infd != -1)
	{
		dup2(head->prev->infd, STDIN_FILENO);
		close(head->prev->infd);
	}
	if (end->outfd != -1)
	{
		dup2(end->outfd, STDOUT_FILENO);
		close(end->outfd);
	}
	if (end->next && end->next->type == PIPE)
		close(end->next->next->infd);
}

static void	execute_redirs_parenthesis(t_shell *shell, t_cmd *head, t_cmd *end)
{
	t_redir	*redir;
	bool	error;

	redir = end->redir;
	error = false;
	while (redir && !error)
	{
		expand_env_arg(shell, &redir->file);
		if (redir->file && open_file(shell, redir))
			change_std_io(redir);
		else if (redir->file)
			error = true;
		redir = redir->next;
	}
	if (!error)
		exec(shell, head, end);
	close_files(end->redir);
}

static void	execute_parenthesis(t_shell *shell, t_cmd *head, t_cmd *end)
{
	pid_t	pid;
	int		status;

	peek_pipes_parenthesis(end);
	pid = safe_fork();
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		manage_pipes_parenthesis(head, end);
		execute_redirs_parenthesis(shell, head, end);
		exit_shell_child(shell);
	}
	else
	{
		waitpid(pid, &status, 0);
		update_exit_status_process(shell, status);
		if (end->outfd >= 0)
			close(end->outfd);
		if (head->prev->infd >= 0)
			close(head->prev->infd);
	}
}

void	manage_parenthesis(t_shell *shell, t_cmd **cmd)
{
	t_cmd	*head;
	t_cmd	*end_node;

	head = *cmd;
	while ((*cmd)->type != CLOSE_PAR)
		*cmd = (*cmd)->next;
	end_node = *cmd;
	execute_parenthesis(shell, head, end_node);
}
