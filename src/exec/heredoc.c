/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorvarea <jorvarea@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 12:07:47 by jorvarea          #+#    #+#             */
/*   Updated: 2024/07/16 12:31:33 by jorvarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*heredoc_input(void)
{
	ft_printf("heredoc> ");
	return (get_next_line(STDIN_FILENO));
}

static void	heredoc2file(t_shell *shell, t_redir *redir, char *heredoc_num)
{
	char	*filename;
	char	*line;
	int		fd;

	filename = ft_strjoin("/tmp/minishell_heredoc", heredoc_num);
	free(heredoc_num);
	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		ft_perror(shell, "open", "");
		free(filename);
		exit(EXIT_FAILURE);
	}
	line = heredoc_input();
	while (line && !equal_str(line, redir->file))
	{
		write(fd, line, ft_strlen(line));
		free(line);
		line = heredoc_input();
	}
	if (line)
		free(line);
	close(fd);
	free(redir->file);
	redir->file = filename;
}

void	save_heredocs(t_shell *shell, t_redir *redir)
{
	int	heredoc_num;

	heredoc_num = 0;
	while (redir)
	{
		if (redir->type == HEREDOC)
			heredoc2file(shell, redir, ft_itoa(heredoc_num++));
		redir = redir->next;
	}
}

void	remove_tmp_heredoc_files(t_redir *redir)
{
	while (redir)
	{
		if (redir->type == HEREDOC)
			unlink(redir->file);
		redir = redir->next;
	}
}
