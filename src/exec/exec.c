/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorvarea <jorvarea@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 16:38:27 by jorvarea          #+#    #+#             */
/*   Updated: 2024/07/16 13:01:04 by jorvarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	open_files(t_shell *shell, t_redir *redir)
{
	bool	no_error;

	no_error = true;
	while (redir && no_error)
	{
		if (redir->type == INFILE)
			redir->fd = open(redir->file, O_RDONLY);
		else if (redir->type == OUTFILE)
			redir->fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (redir->type == IN_APPEND)
			redir->fd = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (redir->fd == -1)
		{
			no_error = false;
			ft_perror(shell, "open", redir->file);
		}
		redir = redir->next;
	}
	return (no_error);
}

void	close_files(t_redir *redir)
{
	while (redir)
	{
		if (redir->file >= 0)
			close(redir->file);
		redir = redir->next;
	}
}

void	execute_redir(t_shell *shell, t_cmd *cmd)
{
	t_redir	*redir;

	redir = cmd->redir;
	save_heredocs(shell, redir);
	if (open_files(shell, redir))
	{
		while (redir)
		{
			if (redir->type == INFILE || redir->type == HEREDOC)
				dup2(redir->fd, STDIN_FILENO);
			else if (redir->type == OUTFILE || redir->type == IN_APPEND)
				dup2(redir->fd, STDOUT_FILENO);
			redir = redir->next;
		}
		execute_cmd(shell, cmd);
		close_files(redir);
	}
	remove_tmp_heredoc_files(redir);
}

void	exec(t_shell *shell, t_cmd *cmd)
{
	while (cmd)
	{
		if (cmd->type == CMD)
			execute_redir(shell, cmd);
		cmd = cmd->next;
	}
}
