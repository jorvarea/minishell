/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 11:52:15 by ana-cast          #+#    #+#             */
/*   Updated: 2024/06/24 16:23:19 by ana-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

pid_t	g_signal;

/*
	TO-DO:
	quitar printf y sustituir por "\n" (mientras es para recordar que Ctrl + C no quitea)
*/
void	signal_handler(int signal)
{
	g_signal = signal;
	// Redisplay the prompt (SIGINT)
	printf("Type 'exit' for quitting minishell\n"); // remove after implementing 'exit'
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

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

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	t_shell	*shell;
	t_cmd	*parsed_input;

	(void)argc;
	(void)argv;
	shell = init_shell(envp);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		signal(SIGINT, signal_handler);
		input = read_input();
		if (!input)
			return (1);
		parsed_input = parser(input);
		free(parsed_input);
		if (!ft_strncmp(input, "exit", 10)) // Quitar IF en el futuro 'exit'
		{
			free(input);
			break ;
		}
	}
	free_shell(shell);
	return (0);
}
