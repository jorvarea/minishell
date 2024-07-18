/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorvarea <jorvarea@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 13:47:51 by jorvarea          #+#    #+#             */
/*   Updated: 2024/07/18 19:44:37 by jorvarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	initialize_signal_handler_cli(void)
{
	g_signal = 0;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, signal_handler_cli);
}

void	signal_handler_cli(int signal)
{
	(void)signal;
	ft_putstr_fd("\n", STDOUT_FILENO);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	initialize_signal_handler_heredoc(void)
{
	g_signal = 0;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, signal_handler_heredoc);
}

void	signal_handler_heredoc(int signal)
{
	g_signal = signal;
	rl_done = 1;
}
