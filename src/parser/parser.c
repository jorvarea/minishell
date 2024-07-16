/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 20:28:08 by ana-cast          #+#    #+#             */
/*   Updated: 2024/07/16 19:23:03 by ana-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_cmd	*parser(char *input, t_shell *shell)
{
	char	**input_array;
	int		i;

	i = -1;
	input = remove_empty_quotes(input, shell);
	if (!input)
		return (NULL);
	input_array = split_input(input);
	if (!input_array)
		return (NULL);
	create_command_list(input_array, shell);
	free_array(&input_array);
	//print_shell(shell, 0, 1);
	return (shell->tokens);
}
