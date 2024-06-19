/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 19:21:11 by ana-cast          #+#    #+#             */
/*   Updated: 2024/06/19 19:27:25 by ana-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	free_array(char **array)
{
	if (array)
	{
		while (*array)
			free(*array++);
	}
	free(array);
}

void	free_commands(t_cmd *command_lst)
{
	t_cmd	*next;

	while (command_lst)
	{
		next = command_lst->next;
		free_array(args);
		free(infile);
		free(outfile);
		free(heredoc);
		free(command_lst);
		command_lst = next;
	}
}

void free_shell(t_shell *shell)
{
	free_array(shell->env);
	free(shell);
}
