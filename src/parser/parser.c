/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 20:28:08 by ana-cast          #+#    #+#             */
/*   Updated: 2024/07/19 21:44:29 by ana-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_cmd	*parser(char *input, t_shell *shell)
{
	char	*p_input;
	char	**input_array;
	char	*org_input;

	org_input = input;
	shell->tokens = NULL;
	input = process_input(input, shell);
	if (!input)
		return (shell->tokens);
	p_input = ft_strtrim(input, " \t\n\v\f\r");
	if (!p_input)
		return (shell->tokens);
	printf("[%i>%i]:|%s|\n", ft_strlen(org_input), ft_strlen(p_input), p_input);
	input_array = split_parser(p_input);
	if (!input_array)
		return (free(p_input), shell->tokens);
	print_array_one_line(input_array, "Split Parser");
	new_token_list(input_array, shell);
	free_array(&input_array);
	return (free(p_input), shell->tokens);
}
