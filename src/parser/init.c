/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 17:44:05 by ana-cast          #+#    #+#             */
/*   Updated: 2024/07/25 18:49:50 by ana-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	event_hook_readline(void)
{
	return (0);
}

static void	disable_echoctl(t_shell *shell)
{
	struct termios	term;

	if (tcgetattr(STDIN_FILENO, &term) == -1)
	{
		ft_perror(shell, "tcgetattr", "");
		exit(EXIT_FAILURE);
	}
	term.c_lflag &= ~ECHOCTL;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &term) == -1)
	{
		ft_perror(shell, "tcsetattr", "");
		exit(EXIT_FAILURE);
	}
}

static void	update_shell_env(t_shell *shell)
{
	char	*minishell_path;
	char	cwd[MAX_ENV_SIZE];

	if (getcwd(cwd, MAX_ENV_SIZE))
	{
		minishell_path = ft_strjoin(cwd, "/minishell");
		if (!update_env(shell, "SHELL", minishell_path))
			add_new_env(shell, "SHELL", minishell_path);
		free(minishell_path);
	}
}

static void	update_shlvl(t_shell *shell)
{
	char	*shlvl;
	int		num;
	char	*new_shlvl;

	shlvl = get_value(shell, "SHLVL");
	if (shlvl)
	{
		num = ft_atoi(shlvl) + 1;
		free(shlvl);
		new_shlvl = ft_itoa(num);
		update_env(shell, "SHLVL", new_shlvl);
		free(new_shlvl);
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
	shell->original_stdin = -1;
	shell->original_stdout = -1;
	shell->l_env = set_env_list(shell->env);
	init_signal_handler_cli();
	disable_echoctl(shell);
	rl_event_hook = event_hook_readline;
	update_shell_env(shell);
	update_shlvl(shell);
	return (shell);
}
