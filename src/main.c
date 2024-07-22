/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorvarea <jorvarea@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 11:52:15 by ana-cast          #+#    #+#             */
/*   Updated: 2024/07/22 23:59:26 by jorvarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

volatile sig_atomic_t	g_signal;

char	*read_input(void)
{
	char	*input;

	input = readline("\001\e[1;35m\002minishell ➜ \001\e[0m\002");
	if (input && input[0] != '\0')
		add_history(input);
	return (input);
}

bool	manage_input(t_shell *shell)
{
	bool	stop;

	stop = false;
	if (shell->tokens)
	{
		if (shell->tokens->args && equal_str(shell->tokens->args[0], "exit"))
			stop = exit_cmd(shell, shell->tokens->args);
		else if (shell->tokens->next == NULL)
			execute_redir(shell, shell->tokens);
		else
			exec(shell);
		free_commands(&shell->tokens);
	}
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
			parser(input, shell);
			stop = manage_input(shell);
		}
	}
	free(input);
	return (exit_shell(shell));
}
