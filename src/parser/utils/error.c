/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 20:22:04 by ana-cast          #+#    #+#             */
/*   Updated: 2024/07/25 17:27:22 by ana-cast         ###   ########.fr       */
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
	else if (error == E_NOMEM)
		ft_putendl_fd(" out of memory", STDERR_FILENO);
	return (NULL);
}

bool	check_redir_args(char **redir, t_shell *shell)
{
	if (array_len(redir) != 2 || !redir[0] || get_redir_type(redir[0]) < 0)
		shell->err_msg = redir[0];
	else if (!redir[1] || get_token_type(redir + 1) != CMD)
		shell->err_msg = redir[1];
	else
		return (0);
	return (E_UTOK);
}

static char	*check_node(t_cmd *node, char *not_prev, int is_par, int *par_check)
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

int	check_token_err(t_shell *shell)
{
	t_cmd	*node;
	int		par_check;

	node = shell->tokens;
	par_check = 0;
	while (node && !shell->err_msg && !(par_check < 0))
	{
		if (node->type == UNKNOWN)
			shell->err_msg = node->args[0];
		else if (node->type == AND || node->type == OR || node->type == PIPE)
			shell->err_msg = check_node(node, "&|(", 0, &par_check);
		else if (node->type == OPEN_PAR)
			shell->err_msg = check_node(node, ")", 1, &par_check);
		else if (node->type == CLOSE_PAR)
			shell->err_msg = check_node(node, "&|(", -1, &par_check);
		node = node->next;
	}
	if (shell->err_msg || par_check)
		return (E_UTOK);
	return (0);
}
