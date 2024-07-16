/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 18:57:35 by ana-cast          #+#    #+#             */
/*   Updated: 2024/07/16 20:09:23 by ana-cast         ###   ########.fr       */
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

t_redir	*get_command_redir(char **args)
{
	t_redir	*redir;
	int		i;

	redir = (t_redir *)malloc(sizeof(t_redir));
	if (!redir)
		return (NULL);
	i = -1;
	while (args[++i])
	{
		if (equal_str(args[i], "<"))
			redir->type = INFILE;
		else if (equal_str(args[i], "<<"))
			redir->type = HEREDOC;
		else if (equal_str(args[i], ">"))
			redir->type = OUTFILE;
		else if (equal_str(args[i], ">>"))
			redir->type = APPEND;
		if (redir->type && args[i + 1])
			redir->file = args[i + 1];
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
	// if (new_cmd->type == CMD)
	// 	new_cmd->redir = get_command_redir(new_cmd->args);
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
