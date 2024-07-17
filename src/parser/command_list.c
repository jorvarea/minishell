/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 18:57:35 by ana-cast          #+#    #+#             */
/*   Updated: 2024/07/17 20:25:39 by ana-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	get_command_type(char **args)
{
	if (!args[0])
		return (UNKNOWN);
	else if (equal_str(args[0], "&&"))
		return (AND);
	else if (equal_str(args[0], "||"))
		return (OR);
	else if (equal_str(args[0], "|"))
		return (PIPE);
	else if (equal_str(args[0], "("))
		return (OPEN_PAR);
	else if (equal_str(args[0], ")"))
		return (CLOSE_PAR);
	return (CMD);
}

t_redir	*add_redir(t_redir *redir, int type, char *file)
{
	t_redir	*new_redir;

	new_redir = (t_redir *)malloc(sizeof(t_redir));
	if (!new_redir)
		return (NULL);
	new_redir->fd = -1;
	new_redir->type = type;
	new_redir->file = ft_strdup(file);
	new_redir->fd = open(new_redir->file, O_RDWR);
	new_redir->next = NULL;
	if (!redir)
	{
		new_redir->prev = NULL;
		redir = new_redir;
	}
	else
	{
		new_redir->prev = redir_last_node(redir);
		redir_last_node(redir)->next = new_redir;
	}
	return (redir);
}

t_redir	*get_command_redir(char **args)
{
	int		i;
	int		type;
	t_redir	*redir;

	i = -1;
	redir = NULL;
	while (args[++i])
	{
		type = 0;
		if (equal_str(args[i], "<"))
			type = INFILE;
		else if (equal_str(args[i], "<<"))
			type = HEREDOC;
		else if (equal_str(args[i], ">"))
			type = OUTFILE;
		else if (equal_str(args[i], ">>"))
			type = APPEND;
		if (type && args[i + 1])
			redir = add_redir(redir, type, args[++i]);
	}
	return (redir);
}

static t_cmd	*assign_cmd_values(t_cmd *new_cmd, char *command)
{
	if (!new_cmd)
		return (NULL);
	new_cmd->cmd = ft_strdup(command);
	new_cmd->args = split_cmd(command);
	if (!new_cmd->cmd || !new_cmd->args)
		return (NULL);
	new_cmd->type = get_command_type(new_cmd->args);
	new_cmd->redir = NULL;
	if (new_cmd->type == CMD)
		new_cmd->redir = get_command_redir(new_cmd->args);
	return (new_cmd);
}

void	create_command_list(char **input_array, t_shell *shell)
{
	int		i;
	t_cmd	*new_cmd;

	i = -1;
	shell->tokens = NULL;
	while (input_array[++i])
	{
		new_cmd = (t_cmd *)malloc(sizeof(t_cmd));
		new_cmd = assign_cmd_values(new_cmd, input_array[i]);
		if (!new_cmd)
			return ;
		new_cmd->next = NULL;
		if (!shell->tokens)
		{
			new_cmd->prev = NULL;
			shell->tokens = new_cmd;
		}
		else
		{
			new_cmd->prev = cmd_last_node(shell->tokens);
			cmd_last_node(shell->tokens)->next = new_cmd;
		}
	}
}
