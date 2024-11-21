/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 18:57:35 by ana-cast          #+#    #+#             */
/*   Updated: 2024/07/25 17:01:02 by ana-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	get_args_number(char **input)
{
	int	len;
	int	stop;

	len = 0;
	stop = 0;
	while (input[len] && !stop)
	{
		if (ft_strchr("();|><&", input[len][0]) && ++stop && !len)
		{
			if (get_token_type(input + len) == REDIR && input[len + 1])
				len++;
		}
		else if (ft_strchr("();|><&", input[len][0]))
			len--;
		len++;
	}
	return (len);
}

static char	**get_token_args(char **args, char **arr, int *i)
{
	int	len;
	int	j;

	len = get_args_number(arr + *i);
	args = (char **)safe_malloc(sizeof(char *) * (len + 1));
	if (!args)
		return (NULL);
	j = 0;
	while (j < len && arr[*i])
		args[j++] = ft_strdup(arr[(*i)++]);
	args[j] = NULL;
	return (args);
}

static t_cmd	*new_token(char **arr, int *pos)
{
	t_cmd	*node;

	node = (t_cmd *)safe_malloc(sizeof(t_cmd));
	if (!node)
		return (NULL);
	node->args = get_token_args(node->args, arr, pos);
	if (!node->args)
		return (free(node), NULL);
	node->type = get_token_type(node->args);
	node->redir = NULL;
	node->pid = -1;
	node->infd = -1;
	node->outfd = -1;
	return (node);
}

int	new_token_list(char **input_array, t_shell *shell)
{
	int		i;
	int		len;
	t_cmd	*new_cmd;

	i = 0;
	len = array_len(input_array);
	shell->tokens = NULL;
	while (i < len)
	{
		new_cmd = new_token(input_array, &i);
		if (!new_cmd)
			return (E_NOMEM);
		new_cmd->next = NULL;
		if (!shell->tokens)
		{
			new_cmd->prev = NULL;
			shell->tokens = new_cmd;
		}
		else
		{
			new_cmd->prev = token_last_node(shell->tokens);
			token_last_node(shell->tokens)->next = new_cmd;
		}
	}
	return (redir_structs(shell));
}
