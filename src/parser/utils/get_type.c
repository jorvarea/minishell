/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_type.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 22:23:51 by ana-cast          #+#    #+#             */
/*   Updated: 2024/07/20 22:41:37 by ana-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	get_token_type(char **args)
{
	if (!args || !args[0])
		return (UNKNOWN);
	if (ft_strchr("();|&", args[0][0]))
	{
		if (equal_str(args[0], "&&"))
			return (AND);
		else if (equal_str(args[0], "||"))
			return (OR);
		else if (equal_str(args[0], "|"))
			return (PIPE);
		else if (equal_str(args[0], "("))
			return (OPEN_PAR);
		else if (equal_str(args[0], ")"))
			return (CLOSE_PAR);
		return (UNKNOWN);
	}
	if (ft_strchr("<>", args[0][0]))
		return (REDIR);
	return (CMD);
}

int	get_redir_type(char *type)
{
	if (equal_str(type, "<"))
		return (INFILE);
	else if (equal_str(type, "<<"))
		return (HEREDOC);
	else if (equal_str(type, ">"))
		return (OUTFILE);
	else if (equal_str(type, ">>"))
		return (APPEND);
	else
		return (NOT_REDIR);
}
