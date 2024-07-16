/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorvarea <jorvarea@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 11:52:15 by ana-cast          #+#    #+#             */
/*   Updated: 2024/07/16 22:29:07 by jorvarea         ###   ########.fr       */
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
	if (input && input[0] != '\0')
		add_history(input);
	return (input);
}

bool	manage_input(t_shell *shell, t_cmd *parsed_input)
{
	bool	stop;

	stop = false;
	if (equal_str(parsed_input->args[0], "exit"))
		stop = exit_cmd(shell, parsed_input->args);
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
	int		status;

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
			if (parsed_input)
				stop = manage_input(shell, parsed_input);
			free_commands(shell->tokens);
		}
	}
	free(input);
	status = shell->exit_status;
	free_shell(shell);
	return (status);
}
