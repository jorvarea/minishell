/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorvarea <jorvarea@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 20:54:42 by jorvarea          #+#    #+#             */
/*   Updated: 2024/07/20 00:47:09 by jorvarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_child_pid(t_pids_array *child_pids, pid_t pid)
{
	if (child_pids->size == child_pids->capacity)
	{
		child_pids->pids = safe_realloc(child_pids->pids, 2
				* child_pids->capacity * sizeof(char *), child_pids->capacity);
		child_pids->capacity *= 2;
	}
	child_pids->pids[child_pids->size++] = pid;
}

void	init_pids_array(t_pids_array *child_pids)
{
	child_pids->pids = (pid_t *)malloc(16 * sizeof(pid_t));
	child_pids->size = 0;
	child_pids->capacity = 16;
}

void	wait_children(t_shell *shell, t_pids_array *child_pids)
{
	int	status;
	int	i;

	i = 0;
	while (i < child_pids->size)
		waitpid(child_pids->pids[i++], &status, 0);
	if (WIFEXITED(status))
		shell->exit_status = WEXITSTATUS(status);
	else
		shell->exit_status = 130;
}
