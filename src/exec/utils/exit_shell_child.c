/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_shell_child.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorvarea <jorvarea@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 13:10:20 by jorvarea          #+#    #+#             */
/*   Updated: 2024/07/25 13:10:36 by jorvarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_shell_child(t_shell *shell)
{
	int	status;

	status = shell->exit_status;
	if (shell->tokens)
		free_tokens(&shell->tokens);
	free_shell(&shell);
	exit(status);
}
