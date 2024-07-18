/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorvarea <jorvarea@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 16:38:27 by jorvarea          #+#    #+#             */
/*   Updated: 2024/07/18 22:42:15 by jorvarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	add_child_pid(t_pids_array *child_pids, pid_t pid)
{
	if (child_pids->size == child_pids->capacity)
	{
		child_pids->pids = safe_realloc(child_pids->pids, 2
				* child_pids->capacity * sizeof(char *), child_pids->capacity);
		child_pids->capacity *= 2;
	}
	child_pids->pids[child_pids->size++] = pid;
}

static void	init_pids_array(t_pids_array *child_pids)
{
	child_pids->pids = (pid_t *)malloc(16 * sizeof(pid_t));
	child_pids->size = 0;
	child_pids->capacity = 16;
}

static void	wait_children(t_pids_array *child_pids)
{
	int	i;

	i = 0;
	while (i < child_pids->size)
		waitpid(child_pids->pids[i++], NULL, 0);
}

void	exec(t_shell *shell, t_cmd *cmd)
{
	t_pids_array	child_pids;
	pid_t			pid;
	int				pipe_des[2];

	init_pids_array(&child_pids);
	while (cmd)
	{
		if (cmd->type == CMD)
		{
			safe_pipe(pipe_des);
			pid = safe_fork();
			if (pid == 0)
			{
				if (cmd->prev && cmd->prev->type == PIPE)
					dup2(pipe_des[0], STDIN_FILENO);
				if (cmd->next && cmd->next->type == PIPE)
					dup2(pipe_des[1], STDOUT_FILENO);
				execute_redir(shell, cmd);
				exit(0);
			}
			else
			{
				close(pipe_des[0]);
				close(pipe_des[1]);
				add_child_pid(&child_pids, pid);
			}
		}
		cmd = cmd->next;
	}
	wait_children(&child_pids);
}
