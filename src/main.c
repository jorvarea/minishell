/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorvarea <jorvarea@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 11:52:15 by ana-cast          #+#    #+#             */
/*   Updated: 2024/07/24 22:07:59 by jorvarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

volatile sig_atomic_t	g_signal;

static char	*read_input(void)
{
	char	*input;

	input = readline("\033[1;35mminishell ➜\033[0m ");
	if (input && input[0] != '\0')
		add_history(input);
	return (input);
}

static void	restore_io(int original_stdin, int original_stdout)
{
	dup2(original_stdin, STDIN_FILENO);
	close(original_stdin);
	dup2(original_stdout, STDOUT_FILENO);
	close(original_stdout);
}

static void	manage_input(t_shell *shell)
{
	int	original_stdout;
	int	original_stdin;

	original_stdin = dup(STDIN_FILENO);
	original_stdout = dup(STDOUT_FILENO);
	save_heredocs(shell);
	if (g_signal != SIGINT && shell->tokens->args && shell->tokens->args[0])
	{
		init_signal_handler_exec();
		if (shell->tokens->next == NULL)
			exec_single_cmd(shell);
		else
			exec(shell);
	}
	init_signal_handler_cli();
	free_tokens(&shell->tokens);
	remove_tmp_heredoc_files(shell);
	restore_io(original_stdin, original_stdout);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	*shell;
	char	*input;

	(void)argc;
	(void)argv;
	shell = init_shell(envp);
	while (true)
	{
		input = read_input();
		if (!input)
			exit_shell(shell);
		else if (input[0] != '\0')
		{
			parser(ft_strdup(input), shell);
			manage_input(shell);
		}
		free(input);
	}
	return (0);
}
