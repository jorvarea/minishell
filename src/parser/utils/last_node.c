/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_node.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 19:48:16 by ana-cast          #+#    #+#             */
/*   Updated: 2024/07/16 20:41:51 by ana-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_cmd	*cmd_last_node(t_cmd *cmd_lst)
{
	if (!cmd_lst)
		return (NULL);
	while (cmd_lst->next)
		cmd_lst = cmd_lst->next;
	return (cmd_lst);
}

t_env	*env_last_node(t_env *l_env)
{
	if (!l_env)
		return (NULL);
	while (l_env->next)
		l_env = l_env->next;
	return (l_env);
}

t_redir	*redir_last_node(t_redir *redir)
{
	if (!redir)
		return (NULL);
	while (redir->next)
		redir = redir->next;
	return (redir);
}
