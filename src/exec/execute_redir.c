/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorvarea <jorvarea@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 13:05:21 by jorvarea          #+#    #+#             */
/*   Updated: 2024/07/22 17:58:15 by jorvarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	open_file(t_shell *shell, t_redir *redir)
{
	bool	no_error;

	no_error = true;
	if (redir->type == INFILE || redir->type == HEREDOC)
		redir->fd = open(redir->file, O_RDONLY);
	else if (redir->type == OUTFILE)
		redir->fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (redir->type == APPEND)
		redir->fd = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (redir->fd == -1)
	{
		no_error = false;
		ft_perror(shell, "open", redir->file);
	}
	return (no_error);
}

static void	close_files(t_redir *redir)
{
	while (redir)
	{
		if (redir->file >= 0)
			close(redir->fd);
		redir = redir->next;
	}
}

static void	change_std_io(t_redir *redir)
{
	if (redir->type == INFILE || redir->type == HEREDOC)
	{
		dup2(redir->fd, STDIN_FILENO);
		close(redir->fd);
	}
	else if (redir->type == OUTFILE || redir->type == APPEND)
	{
		dup2(redir->fd, STDOUT_FILENO);
		close(redir->fd);
	}
}

static void	restore_prev_io(int prev_stdin, int prev_stdout)
{
	dup2(prev_stdin, STDIN_FILENO);
	close(prev_stdin);
	dup2(prev_stdout, STDOUT_FILENO);
	close(prev_stdout);
}

void	execute_redir(t_shell *shell, t_cmd *cmd, int prev_stdin, int prev_stdout)
{
	t_redir	*redir;
	bool	error;

	redir = cmd->redir;
	error = false;
	save_heredocs(shell, redir);
	while (redir && !error)
	{
		if (redir->file && open_file(shell, redir))
			change_std_io(redir);
		else if (redir->file)
			error = true;
		redir = redir->next;
	}
	if (!error)
		execute_cmd(shell, cmd);
	restore_prev_io(prev_stdin, prev_stdout);
	close_files(cmd->redir);
	remove_tmp_heredoc_files(cmd->redir);
}
