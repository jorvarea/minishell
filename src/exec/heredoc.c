/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorvarea <jorvarea@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 12:07:47 by jorvarea          #+#    #+#             */
/*   Updated: 2024/07/23 01:55:29 by jorvarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	manage_open_error(t_shell *shell, char *filename)
{
	ft_perror(shell, "open", filename);
	free(filename);
	exit(EXIT_FAILURE);
}

static void	manage_end_heredoc(t_redir *redir, char *filename, char *line)
{
	if (line)
	{
		free(line);
		free(redir->file);
		redir->file = filename;
	}
	else if (g_signal == SIGINT)
	{
		unlink(filename);
		free(filename);
		free(redir->file);
		redir->file = NULL;
		g_signal = 0;
	}
	else
	{
		ft_putstr_fd("minishell: warning: here-document ", STDERR_FILENO);
		ft_putstr_fd("delimited by end-of-file (wanted `", STDERR_FILENO);
		ft_putstr_fd(redir->file, STDERR_FILENO);
		ft_putendl_fd("')", STDERR_FILENO);
		free(redir->file);
		redir->file = filename;
	}
}

static void	heredoc2file(t_shell *shell, t_redir *redir, char *heredoc_num)
{
	char	*filename;
	char	*line;
	int		fd;

	filename = generate_filename(heredoc_num);
	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (fd == -1)
		manage_open_error(shell, filename);
	line = readline("heredoc> ");
	while (line && !equal_str(line, redir->file) && g_signal != SIGINT)
	{
		if (line[0] == '\0')
		{
			free(line);
			line = ft_strdup("\n");
		}
		expand_arg_heredoc(shell, &line);
		write(fd, line, ft_strlen(line));
		free(line);
		line = readline("heredoc> ");
	}
	close(fd);
	manage_end_heredoc(redir, filename, line);
}

static void	save_heredocs_cmd(t_shell *shell, t_cmd *cmd, int *heredoc_num)
{
	t_redir *redir;

	redir = cmd->redir;
	while (redir)
	{
		if (redir->type == HEREDOC)
			heredoc2file(shell, redir, ft_itoa((*heredoc_num)++));
		redir = redir->next;
	}
}

void save_heredocs(t_shell *shell)
{
	t_cmd *cmd;
	int heredocs_num;

	initialize_signal_handler_heredoc();
	cmd = shell->tokens;
	heredocs_num = 0;
	while (cmd)
	{
		save_heredocs_cmd(shell, cmd, &heredocs_num);
		cmd = cmd->next;
	}
	initialize_signal_handler_cli();
}
