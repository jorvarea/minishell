/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorvarea <jorvarea@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 11:52:15 by ana-cast          #+#    #+#             */
/*   Updated: 2024/07/10 17:39:10 by jorvarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

pid_t	g_signal;

void	signal_handler(int signal)
{
	g_signal = signal;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

char	*read_input(void)
{
	char	*input;

	input = readline("\033[1;35mminishell ➜\033[0m ");
	return (input);
}

bool	manage_input(t_shell *shell, t_cmd *parsed_input, char *input)
{
	bool	stop;

	parsed_input = chatgpt_parse_input(input);
	stop = false;
	if (equal_str(parsed_input->args[0], "exit"))
	{
		exit_cmd(shell, parsed_input->args);
		stop = true;
	}
	else
		exec(shell, parsed_input);
	free_array(&parsed_input->args);
	free(parsed_input);
	return (stop);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	*shell;
	t_cmd	*parsed_input;
	char	*input;
	bool	stop;

	(void)argc;
	(void)argv;
	shell = init_shell(envp);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, signal_handler);
	stop = false;
	while (!stop)
	{
		input = read_input();
		if (!input)
			stop = true;
		else if (input[0] != '\0')
		{
			parsed_input = parser(input, shell);
			stop = manage_input(shell, parsed_input, input);
		}
	}
	free(input);
	free_shell(shell);
	return (0);
}
