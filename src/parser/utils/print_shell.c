/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_shell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 14:54:05 by ana-cast          #+#    #+#             */
/*   Updated: 2024/07/20 21:11:05 by ana-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	print_redir_type(int type)
{
	if (type == NOT_REDIR)
		printf("NOT REDIR(%i)", type);
	else if (type == INFILE)
		printf("INFILE(%i:\'<\')", type);
	else if (type == APPEND)
		printf("APPEND(%i:\'>>')", type);
	else if (type == OUTFILE)
		printf("OUTFILE(%i:\'>')", type);
	else if (type == HEREDOC)
		printf("HEREDOC(%i:\'<<')", type);
}

void	print_type(int type)
{
	if (type == 0)
		printf("-> CMD(%i)", type);
	else if (type == 1)
		printf ("-> AND(%i)", type);
	else if (type == 2)
		printf ("-> OR(%i)", type);
	else if (type == 4)
		printf ("-> PIPE(%i)", type);
	else if (type == 5)
		printf ("-> OPEN PARENTHESIS(%i)", type);
	else if (type == 6)
		printf ("-> CLOSE PARENTHESIS(%i)", type);
	else if (type == 7)
		printf ("-> REDIR(%i)", type);
	else
		printf ("-> UNKNOWN(%i)", type);
}

void	print_command_list(t_cmd *tokens)
{
	t_cmd	*tok_next;
	t_redir	*red_next;
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
		while (tokens->redir)
		{
			red_next = tokens->redir->next;
			printf("\tREDIR:\n\t -FD:%i \n\t -TYPE:", tokens->redir->fd);
			print_redir_type(tokens->redir->type);
			printf("\n\t -FILE:|%s|\n", tokens->redir->file);
			tokens->redir = red_next;
		}
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
