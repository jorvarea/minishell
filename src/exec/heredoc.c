/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorvarea <jorvarea@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 12:07:47 by jorvarea          #+#    #+#             */
/*   Updated: 2024/07/16 21:51:01 by jorvarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	expand_arg_heredoc(t_shell *shell, char **ptr_arg)
{
	t_quotes	quotes;
	char		*arg;
	int			i;

	arg = *ptr_arg;
	ft_memset(&quotes, 0, sizeof(quotes));
	i = 0;
	while (arg[i])
	{
		if (arg[i] == '$' && arg[i + 1] == '?')
			replace_exit_status(shell, ptr_arg, i);
		else if (arg[i] == '$')
			replace_env(shell, ptr_arg, i);
		arg = *ptr_arg;
		i++;
	}
}

static char	*generate_filename(char *heredoc_num)
{
	char	*filename;

	filename = ft_strjoin("/tmp/minishell_heredoc", heredoc_num);
	free(heredoc_num);
	return (filename);
}

static void	heredoc2file(t_shell *shell, t_redir *redir, char *heredoc_num)
{
	char	*filename;
	char	*line;
	int		fd;

	filename = generate_filename(heredoc_num);
	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (fd == -1)
	{
		ft_perror(shell, "open", "");
		free(filename);
		exit(EXIT_FAILURE);
	}
	line = readline("heredoc> ");
	while (line && !equal_str(line, redir->file))
	{
		expand_arg_heredoc(shell, &line);
		write(fd, line, ft_strlen(line));
		free(line);
		line = readline("heredoc> ");
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
