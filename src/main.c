/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 11:52:15 by ana-cast          #+#    #+#             */
/*   Updated: 2024/05/17 20:51:05 by ana-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	exit_program_nl(void)
{
	printf("\n");
	exit(EXIT_SUCCESS);
}

char	*read_input(void)
{
	char	*input;

	input = readline("\033[0;31mminishell >\033[0m");
	if (!input)
		exit_program_nl();
	return (input);
}

int	main(int argc, char **argv)
{
	char		*input;
	t_parsed	*parsed_input;

	(void)argv;
	if (argc == 1)
	{
		while (1)
		{
			input = read_input();
			if (!input)
				return (0);
			parsed_input = parser(input);
			free(input);
			free(parsed_input);
		}
	}
	else
		ft_putstr_fd("Invalid number of arguments", 2);
	return (1);
}
