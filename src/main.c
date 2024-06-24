/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 11:52:15 by ana-cast          #+#    #+#             */
/*   Updated: 2024/06/24 18:23:51 by ana-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

pid_t	g_signal;

/*
	FUNCTIONALITY:
	 - Updates g_signal (global variable) with signal received (SIGINT)
	 - Redisplays the prompt when receiving SIGINT (printf should only be '\n')
	TO-DO:
	quitar printf y sustituir por "\n" (Ahora recuerda que Ctrl + C no quitea)
*/
void	signal_handler(int signal)
{
	g_signal = signal;
	printf("Type 'exit' for quitting minishell\n");
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

/*
	TO-DO:
	quitar if (!ft_strncmp(input, "exit", 10)) cuando implementemos 'exit'
*/
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
		parsed_input = parser(input, shell);
		free(parsed_input);
		if (!ft_strncmp(input, "exit", 10))
		{
			free(input);
			break ;
		}
	}
	free_shell(shell);
	return (0);
}
