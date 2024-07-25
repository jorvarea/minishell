/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorvarea <jorvarea@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 11:52:15 by ana-cast          #+#    #+#             */
/*   Updated: 2024/07/25 00:52:22 by jorvarea         ###   ########.fr       */
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

static void	restore_io(t_shell *shell)
{
	dup2(shell->original_stdin, STDIN_FILENO);
	close(shell->original_stdin);
	dup2(shell->original_stdout, STDOUT_FILENO);
	close(shell->original_stdout);
}

static void	manage_input(t_shell *shell)
{
	shell->original_stdin = dup(STDIN_FILENO);
	shell->original_stdout = dup(STDOUT_FILENO);
	save_heredocs(shell);
	if (g_signal != SIGINT && shell->tokens->args && shell->tokens->args[0])
	{
		init_signal_handler_exec();
		if (shell->tokens->next == NULL)
			exec_single_cmd(shell);
		else
			exec(shell, shell->tokens, NULL);
	}
	init_signal_handler_cli();
	free_tokens(&shell->tokens);
	remove_tmp_heredoc_files(shell);
	restore_io(shell);
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
