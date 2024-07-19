/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorvarea <jorvarea@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 11:52:15 by ana-cast          #+#    #+#             */
/*   Updated: 2024/07/19 22:11:06 by jorvarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

volatile sig_atomic_t	g_signal;

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
	if (!parsed_input)
		return (stop);
	if (equal_str(parsed_input->args[0], "exit"))
		stop = exit_cmd(shell, parsed_input->args);
	else if (parsed_input->next == NULL)
		exec_one(shell, parsed_input);
	else
		exec(shell, parsed_input);
	free_array(&parsed_input->args);
	free(parsed_input);
	free_commands(shell->tokens);
	return (stop);
}

int	exit_shell(t_shell *shell)
{
	int	status;

	status = shell->exit_status;
	printf("exit\n");
	free_shell(shell);
	return (status);
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
	stop = false;
	while (!stop)
	{
		input = read_input();
		if (!input)
			stop = true;
		else if (input[0] != '\0')
		{
			parsed_input = parser(input, shell);
			stop = manage_input(shell, parsed_input);
		}
	}
	free(input);
	return (exit_shell(shell));
}
