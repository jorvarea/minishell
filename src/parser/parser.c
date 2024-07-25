/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 20:28:08 by ana-cast          #+#    #+#             */
/*   Updated: 2024/07/25 16:27:29 by ana-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_cmd	*parser(char *input, t_shell *shell)
{
	char	*p_input;
	char	**input_array;
	int		list_error;

	shell->tokens = NULL;
	shell->parser_error = 0;
	input = process_input(input, shell);
	if (!input)
		return (shell->tokens);
	p_input = ft_strtrim(input, " \t\n\v\f\r");
	free_str(&input);
	if (!p_input)
		return (shell->tokens);
	input_array = split_parser(p_input);
	if (!input_array)
		return (free(p_input), shell->tokens);
	shell->parser_error = new_token_list(input_array, shell);
	free_array(&input_array);
	free(p_input);
	update_token_list(shell);
	if (shell->parser_error || check_token_err(shell))
		shell->parser_error = 1;
	return (shell->tokens);
}
