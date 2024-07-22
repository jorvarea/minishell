/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorvarea <jorvarea@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 16:38:27 by jorvarea          #+#    #+#             */
/*   Updated: 2024/07/22 13:50:04 by jorvarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h" 

static void	exec_left(t_shell *shell, t_cmd *cmd, int pipe_fds[2], int original_stdin)
{
	int current_stdin;
	
	printf("izq\n");
	if (cmd->prev->prev && cmd->prev->prev->type == PIPE)
	{
		safe_dup2(pipe_fds[0], STDIN_FILENO);
		close(pipe_fds[0]);
		current_stdin = pipe_fds[0];
	}
	else
		current_stdin = original_stdin;
	safe_dup2(pipe_fds[1], STDOUT_FILENO);
	close(pipe_fds[1]);
	execute_redir(shell, cmd->prev, current_stdin, pipe_fds[1]);
	close(pipe_fds[0]);
	close(pipe_fds[1]);
	exit(shell->exit_status);
}

void	exec(t_shell *shell, t_cmd *cmd, int original_stdin, int original_stdout)
{
	pid_t	pid;
	int		pipe_fds[2];

	if (!cmd->next)
	{
		printf("last\n");
		close(pipe_fds[1]);
		safe_dup2(original_stdout, STDOUT_FILENO);
        close(original_stdout);
		if (cmd->prev->type == PIPE)
		{
			safe_dup2(pipe_fds[0], STDIN_FILENO);
			ft_putendl_fd("klk", 2);
			close(pipe_fds[0]);
			
		}
        execute_redir(shell, cmd, pipe_fds[0], STDOUT_FILENO);
		close(pipe_fds[0]);
		safe_dup2(original_stdin, STDIN_FILENO);
        close(original_stdin);
        return ;
	}
	if (cmd->type == CMD)
		cmd = cmd->next;
	safe_pipe(pipe_fds);
	pid = safe_fork();
	if (pid == 0)
		exec_left(shell, cmd, pipe_fds, original_stdin);
	else
	{
		printf("der\n");
		exec(shell, cmd->next, original_stdin, original_stdout);
		waitpid(pid, NULL, 0);
	}
}
