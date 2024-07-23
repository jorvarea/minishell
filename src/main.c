/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorvarea <jorvarea@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 11:52:15 by ana-cast          #+#    #+#             */
/*   Updated: 2024/07/23 02:15:38 by jorvarea         ###   ########.fr       */
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

void	restore_io(int original_stdin, int original_stdout)
{
	dup2(original_stdin, STDIN_FILENO);
	dup2(original_stdout, STDOUT_FILENO);
	close(original_stdin);
	close(original_stdout);
}

bool	manage_input(t_shell *shell)
{
	bool	stop;
	int		original_stdout;
	int		original_stdin;

	original_stdin = dup(STDIN_FILENO);
	original_stdout = dup(STDOUT_FILENO);
	save_heredocs(shell);
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
	remove_tmp_heredoc_files(shell);
	restore_io(original_stdin, original_stdout);
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
