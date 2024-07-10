/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chatgpt_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorvarea <jorvarea@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 17:26:33 by jorvarea          #+#    #+#             */
/*   Updated: 2024/07/10 17:34:00 by jorvarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_arg(t_args **l_args, char *arg)
{
	t_args	*new_arg;
	t_args	*temp;

	new_arg = (t_args *)malloc(sizeof(t_args));
	new_arg->arg = strdup(arg);
	new_arg->next = NULL;
	new_arg->prev = NULL;
	if (!*l_args)
		*l_args = new_arg;
	else
	{
		temp = *l_args;
		while (temp->next)
			temp = temp->next;
		temp->next = new_arg;
		new_arg->prev = temp;
	}
}

void	add_redir(t_redir **redir_list, char *file, t_type_redir type)
{
	t_redir	*new_redir;
	t_redir	*temp;

	new_redir = (t_redir *)malloc(sizeof(t_redir));
	new_redir->file = strdup(file);
	new_redir->type = type;
	new_redir->next = NULL;
	new_redir->prev = NULL;
	if (!*redir_list)
	{
		*redir_list = new_redir;
	}
	else
	{
		temp = *redir_list;
		while (temp->next)
			temp = temp->next;
		temp->next = new_redir;
		new_redir->prev = temp;
	}
}

t_token	get_token_type(char *token)
{
	if (strcmp(token, "&&") == 0)
		return (AND);
	if (strcmp(token, "||") == 0)
		return (OR);
	if (strcmp(token, "|") == 0)
		return (PIPE);
	if (strcmp(token, "(") == 0)
		return (OPEN_PAR);
	if (strcmp(token, ")") == 0)
		return (CLOSE_PAR);
	return (CMD);
}

t_cmd	*create_cmd_node(t_token type)
{
	t_cmd	*node;

	node = (t_cmd *)malloc(sizeof(t_cmd));
	node->type = type;
	node->cmd = NULL;
	node->args = NULL;
	node->l_args = NULL;
	node->redir = NULL;
	node->next = NULL;
	node->prev = NULL;
	return (node);
}

void	add_cmd(t_cmd **cmd_list, t_cmd *new_cmd)
{
	t_cmd	*temp;

	if (!*cmd_list)
		*cmd_list = new_cmd;
	else
	{
		temp = *cmd_list;
		while (temp->next)
			temp = temp->next;
		temp->next = new_cmd;
		new_cmd->prev = temp;
	}
}

t_cmd	*chatgpt_parse_input(char *input)
{
	char	**tokens;
	int		num_tokens;
	t_cmd	*cmd_list;
	t_cmd	*current_cmd;
	int		i;
	t_token	type;
	int		j;

	cmd_list = NULL;
	current_cmd = NULL;
	tokens = ft_split(input, ' ');
	num_tokens = count_words(tokens);
	for (i = 0; i < num_tokens; i++)
	{
		type = get_token_type(tokens[i]);
		if (type == CMD)
		{
			if (!current_cmd || current_cmd->type != CMD)
			{
				current_cmd = create_cmd_node(CMD);
				add_cmd(&cmd_list, current_cmd);
			}
			if (!current_cmd->cmd)
			{
				current_cmd->cmd = strdup(tokens[i]);
				current_cmd->args = (char **)malloc(sizeof(char *) * (num_tokens
						- i + 1));
				current_cmd->args[0] = strdup(tokens[i]);
				current_cmd->args[1] = NULL;
			}
			else
			{
				j = 0;
				while (current_cmd->args[j])
					j++;
				current_cmd->args[j] = strdup(tokens[i]);
				current_cmd->args[j + 1] = NULL;
			}
			add_arg(&current_cmd->l_args, tokens[i]);
		}
		else
		{
			current_cmd = create_cmd_node(type);
			add_cmd(&cmd_list, current_cmd);
		}
	}
	free_array(&tokens);
	return (cmd_list);
}
