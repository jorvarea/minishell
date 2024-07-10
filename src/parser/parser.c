/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 20:28:08 by ana-cast          #+#    #+#             */
/*   Updated: 2024/07/10 15:30:04 by ana-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_cmd	*parser(char *input, t_shell *shell)
{
	t_cmd	*command_lst;
	char	**commands;
	char	**input_array;
	int		i;

	(void)shell;
	i = -1;
	input_array = split_input(input);
	if (!input_array)
		return (NULL);
	print_array(input_array);
	while (input_array[++i])
	{
		commands = split_cmd(input_array[i]);
		print_array(commands);
		free_array(&commands);
	}
	free_array(&input_array);
	command_lst = (t_cmd *)malloc(sizeof(t_cmd));
	if (!command_lst)
		return (NULL);
	return (command_lst);
}
