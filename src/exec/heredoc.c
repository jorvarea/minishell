/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorvarea <jorvarea@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 12:07:47 by jorvarea          #+#    #+#             */
/*   Updated: 2024/07/17 22:39:45 by jorvarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*generate_filename(char *heredoc_num)
{
	char	*filename;

	filename = ft_strjoin("/tmp/minishell_heredoc", heredoc_num);
	free(heredoc_num);
	return (filename);
}

static void	manage_open_error(t_shell *shell, char *filename)
{
	ft_perror(shell, "open", filename);
	free(filename);
	exit(EXIT_FAILURE);
}

static void	manage_end_heredoc(char *line, char *limit_word)
{
	if (line)
		free(line);
	else
	{
		ft_putstr_fd("minishell: warning: here-document ", STDERR_FILENO);
		ft_putstr_fd("delimited by end-of-file (wanted `", STDERR_FILENO);
		ft_putstr_fd(limit_word, STDERR_FILENO);
		ft_putendl_fd("')", STDERR_FILENO);
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
		expand_arg_heredoc(shell, &line);
		write(fd, line, ft_strlen(line));
		free(line);
		line = readline("heredoc> ");
	}
	manage_end_heredoc(line, redir->file);
	close(fd);
	free(redir->file);
	redir->file = filename;
}

void	save_heredocs(t_shell *shell, t_redir *redir)
{
	int	heredoc_num;

	initialize_signal_handler_heredoc();
	heredoc_num = 0;
	while (redir)
	{
		if (redir->type == HEREDOC)
			heredoc2file(shell, redir, ft_itoa(heredoc_num++));
		redir = redir->next;
	}
	initialize_signal_handler_cli();
}
