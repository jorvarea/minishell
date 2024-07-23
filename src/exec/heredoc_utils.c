/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorvarea <jorvarea@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 22:12:19 by jorvarea          #+#    #+#             */
/*   Updated: 2024/07/23 02:08:32 by jorvarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*generate_filename(char *heredoc_num)
{
	char	*filename;

	filename = ft_strjoin("/tmp/minishell_heredoc", heredoc_num);
	free(heredoc_num);
	return (filename);
}

void	expand_arg_heredoc(t_shell *shell, char **ptr_arg)
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

void	remove_tmp_heredoc_files(t_shell *shell)
{
	t_cmd	*cmd;
	t_redir	*redir;

	cmd = shell->tokens;
	while (cmd)
	{
		redir = cmd->redir;
		while (redir)
		{
			if (redir->type == HEREDOC)
				unlink(redir->file);
			redir = redir->next;
		}
		cmd = cmd->next;
	}
}
