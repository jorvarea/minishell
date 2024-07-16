/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorvarea <jorvarea@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 13:05:21 by jorvarea          #+#    #+#             */
/*   Updated: 2024/07/16 21:24:15 by jorvarea         ###   ########.fr       */
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
		dup2(redir->fd, STDIN_FILENO);
	else if (redir->type == OUTFILE || redir->type == APPEND)
		dup2(redir->fd, STDOUT_FILENO);
}

void	execute_redir(t_shell *shell, t_cmd *cmd)
{
	t_redir	*redir;
	int		original_stdin;
	int		original_stdout;
	bool	error;

	original_stdin = dup(STDIN_FILENO);
	original_stdout = dup(STDOUT_FILENO);
	redir = cmd->redir;
	error = false;
	save_heredocs(shell, redir);
	while (redir && !error)
	{
		if (open_file(shell, redir))
			change_std_io(redir);
		else
			error = true;
		redir = redir->next;
	}
	if (!error)
		execute_cmd(shell, cmd);
	dup2(original_stdin, STDIN_FILENO);
	dup2(original_stdout, STDOUT_FILENO);
	close_files(cmd->redir);
	remove_tmp_heredoc_files(cmd->redir);
}