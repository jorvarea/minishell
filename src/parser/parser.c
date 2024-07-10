/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 20:28:08 by ana-cast          #+#    #+#             */
/*   Updated: 2024/07/10 16:37:37 by ana-cast         ###   ########.fr       */
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
	printf("%sINPUT>%s ", RED, WHITE);
	input_array = split_input(input);
	if (!input_array)
		return (NULL);
	print_array(input_array);
	printf("\n%sCOMMANDS>%s ", RED, WHITE);
	commands = split_cmd(input);
	if (!commands)
		return (free_array(&input_array), NULL);
	print_array(commands);
	// while (input_array[++i])
	// {
	// 	commands = split_cmd(input_array[i]);
	// 	print_array(commands);
	// 	free_array(&commands);
	// }
	free_array(&input_array);
	free_array(&commands);
	command_lst = (t_cmd *)malloc(sizeof(t_cmd));
	if (!command_lst)
		return (NULL);
	return (command_lst);
}
