/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorvarea <jorvarea@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 17:44:05 by ana-cast          #+#    #+#             */
/*   Updated: 2024/07/18 17:28:01 by jorvarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void disable_echoctl(t_shell *shell) 
{
    struct termios term;

    if (tcgetattr(STDIN_FILENO, &term) == -1) {
        ft_perror(shell, "tcgetattr", "");
        exit(EXIT_FAILURE);
    }
    term.c_lflag &= ~ECHOCTL;
    if (tcsetattr(STDIN_FILENO, TCSANOW, &term) == -1) {
        ft_perror(shell, "tcsetattr", "");
        exit(EXIT_FAILURE);
    }
}

t_shell	*init_shell(char **envp)
{
	t_shell	*shell;

	shell = (t_shell *)malloc(sizeof(t_shell));
	if (!shell)
		exit_program_nl();
	shell->env = init_shell_env(envp);
	shell->exit_status = 0;
	shell->tokens = NULL;
	shell->l_env = set_env_list(shell->env);
	shell->files = NULL;
	initialize_signal_handler_cli();
	disable_echoctl(shell);
	return (shell);
}
