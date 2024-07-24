/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_shell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 14:54:05 by ana-cast          #+#    #+#             */
/*   Updated: 2024/07/24 12:08:51 by ana-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	print_token_redir(t_cmd *token)
{
	t_redir	*tk_redir;
	t_redir	*rd_next;

	tk_redir = token->redir;
	while (tk_redir)
	{
		rd_next = tk_redir->next;
		printf("\tREDIR:\n\t -FD:%i \n\t -TYPE:", tk_redir->fd);
		print_redir_type(tk_redir->type);
		printf("\n\t -FILE:|%s|\n", tk_redir->file);
		tk_redir = rd_next;
	}
}

void	print_command_list(t_cmd *tokens)
{
	t_cmd	*tok_next;
	int		i;

	i = 0;
	printf("\n%sCOMMAND LIST>\n%s", RED, WHITE);
	if (!tokens)
		printf("\t%s(null)%s\n\n", YELLOW, WHITE);
	while (tokens)
	{
		tok_next = tokens->next;
		printf("%sTOK[%i] %s", BOLD, i++, WHITE);
		print_array_one_line(tokens->args, NULL);
		print_type(tokens->type);
		printf("\n");
		print_token_redir(tokens);
		tokens = tok_next;
	}
}

void	print_shell_l_env(t_env *l_env)
{
	t_env	*next;
	int		i;

	i = 0;
	printf("\n%sT_ENV *L_ENV>%s\n", RED, WHITE);
	while (l_env)
	{
		next = l_env->next;
		printf("\t[%i] ", i++);
		printf("%sKEY:%s%s\n\t", GREEN, WHITE, l_env->key);
		printf("%sVALUE:%s%s\n", GREEN, WHITE, l_env->value);
		l_env = next;
	}
}

void	print_shell(t_shell *shell, bool env, bool tokens)
{
	printf("\n%s%sPRINTING SHELL>%s\n\n", MAGENTA, BOLD, WHITE);
	printf("%sEXIT STATUS>%s %i", RED, WHITE, shell->exit_status);
	if (env)
	{
		print_array(shell->env, "CHAR **ENV");
		print_shell_l_env(shell->l_env);
	}
	if (tokens)
		print_command_list(shell->tokens);
	printf("\n\n%s%s<FINISHED PRINTING SHELL%s\n\n", MAGENTA, BOLD, WHITE);
}
