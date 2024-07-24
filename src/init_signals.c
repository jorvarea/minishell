/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_signals.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorvarea <jorvarea@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 17:24:24 by jorvarea          #+#    #+#             */
/*   Updated: 2024/07/24 17:30:41 by jorvarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_signal_handler_exec(void)
{
	g_signal = 0;
	signal(SIGQUIT, sigquit_handler);
	signal(SIGINT, SIG_IGN);
}

void	init_signal_handler_heredoc(void)
{
	g_signal = 0;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, signal_handler_heredoc);
}

void	init_signal_handler_cli(void)
{
	g_signal = 0;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, signal_handler_cli);
}
