/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorvarea <jorvarea@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 18:22:55 by jorvarea          #+#    #+#             */
/*   Updated: 2024/06/27 18:23:02 by jorvarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void set_and_print_minishell_error(t_shell *shell, char* msg)
{
	shell->exit_status = 1;
    ft_putendl_fd(msg, STDERR_FILENO);
}

void set_and_print_perror(t_shell *shell, char* msg)
{
	shell->exit_status = 1;
    perror(msg);
}
