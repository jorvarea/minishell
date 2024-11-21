/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorvarea <jorvarea@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 13:05:21 by jorvarea          #+#    #+#             */
/*   Updated: 2024/07/25 16:06:00 by jorvarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	open_file(t_shell *shell, t_redir *redir)
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

void	close_files(t_redir *redir)
{
	while (redir)
	{
		if (redir->fd >= 0)
			close(redir->fd);
		redir = redir->next;
	}
}

void	change_std_io(t_redir *redir)
{
	if (redir->type == INFILE || redir->type == HEREDOC)
		dup2(redir->fd, STDIN_FILENO);
	else if (redir->type == OUTFILE || redir->type == APPEND)
		dup2(redir->fd, STDOUT_FILENO);
}

void	execute_redir(t_shell *shell, t_cmd *cmd)
{
	t_redir	*redir;
	bool	error;

	redir = cmd->redir;
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
		execute_cmd(shell, cmd);
	close_files(cmd->redir);
}
