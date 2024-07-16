/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorvarea <jorvarea@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 20:28:08 by ana-cast          #+#    #+#             */
/*   Updated: 2024/07/16 16:44:39 by jorvarea         ###   ########.fr       */
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
	input = remove_empty_quotes(input, shell);
	if (!input)
		return (NULL);
	printf("%sINPUT>%s ", RED, WHITE);
	input_array = split_input(input);
	if (!input_array)
		return (NULL);
	print_array(input_array, "INPUT ARRAY");
	printf("\n%sCOMMANDS>%s ", RED, WHITE);
	while (input_array[++i])
	{
		commands = split_cmd(input_array[i]);
		print_array(commands, "COMMANDS");
		free_array(&commands);
	}
	free_array(&input_array);
	command_lst = (t_cmd *)malloc(sizeof(t_cmd));
	if (!command_lst)
		return (NULL);
	return (command_lst);
}
