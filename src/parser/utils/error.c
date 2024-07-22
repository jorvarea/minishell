/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 20:22:04 by ana-cast          #+#    #+#             */
/*   Updated: 2024/07/22 19:50:15 by ana-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	*parser_error(int error, char *str, int exit_code, t_shell *shell)
{
	shell->exit_status = exit_code;
	ft_putstr_fd("-minishell: ", STDERR_FILENO);
	if (error == E_UQUOTE)
		ft_putendl_fd("parser error: unclosed quotes", STDERR_FILENO);
	else if (error == E_UTOK)
	{
		ft_putstr_fd("syntax error near unexpected token `", STDERR_FILENO);
		if (str && str[0])
			ft_putstr_fd(str, STDERR_FILENO);
		ft_putendl_fd("\'", STDERR_FILENO);
	}
	else if (error == ENOMEM)
		ft_putendl_fd(" out of memory", STDERR_FILENO);
	return (NULL);
}

char	*check_node(t_cmd *node, char *not_prev, int is_par, int *par_check)
{
	t_cmd	*prev;

	prev = node->prev;
	*par_check += is_par;
	if (array_len(node->args) > 1)
		return (node->args[1]);
	if (!is_par && (!prev || !node->next))
		return (node->args[0]);
	if (prev && node->type == OPEN_PAR && prev->type == CMD)
		return (node->args[0]);
	if (node->next && node->type == CLOSE_PAR && node->next->type == CMD)
		return (node->next->args[0]);
	if (prev && prev->type != CMD && ft_strchr(not_prev, prev->args[0][0]))
		return (node->args[0]);
	return (NULL);
}

int	check_error_tokens(t_shell *shell)
{
	t_cmd	*node;
	char	*error;
	int		par_check;

	node = shell->tokens;
	error = NULL;
	par_check = 0;
	while (node && !error && !(par_check < 0))
	{
		if (node->type == REDIR || node->type == UNKNOWN)
			error = node->args[0];
		else if (node->type == AND || node->type == OR || node->type == PIPE)
			error = check_node(node, "&|(", 0, &par_check);
		else if (node->type == OPEN_PAR)
			error = check_node(node, ")", 1, &par_check);
		else if (node->type == CLOSE_PAR)
			error = check_node(node, "&|(", -1, &par_check);
		node = node->next;
	}
	if (error || par_check)
		return (parser_error(E_UTOK, error, E_UTOK, shell), 1);
	return (0);
}
