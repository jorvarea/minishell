/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 14:54:05 by ana-cast          #+#    #+#             */
/*   Updated: 2024/07/17 19:56:13 by ana-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	print_type(int type, int isToken)
{
	if (type == 0 && isToken)
		printf("-> CMD(%i)", type);
	else if (type == 1 && isToken)
		printf ("-> AND(%i)", type);
	else if (type == 2 && isToken)
		printf ("-> OR(%i)", type);
	else if (type == 4 && isToken)
		printf ("-> PIPE(%i)", type);
	else if (type == 5 && isToken)
		printf ("-> OPEN PARENTHESIS(%i)", type);
	else if (type == 6 && isToken)
		printf ("-> CLOSE PARENTHESIS(%i)", type);
	else if (isToken)
		printf ("-> UNKNOWN(%i)", type);
	else if (type == 0)
		printf("NOT REDIR(%i)", type);
	else if (type == 1)
		printf("INFILE(%i:\'<\')", type);
	else if (type == 2)
		printf("APPEND(%i:\'>>')", type);
	else if (type == 3)
		printf("OUTFILE(%i:\'>')", type);
	else if (type == 4)
		printf("HEREDOC(%i:\'<<')", type);
}

void	print_command_list(t_cmd *tokens)
{
	t_cmd	*tok_next;
	t_redir	*red_next;
	int		i;

	i = 0;
	printf("\n%sCOMMAND LIST>%s", RED, WHITE);
	if (!tokens)
		printf("\t%s(null)%s\n\n", YELLOW, WHITE);
	while (tokens)
	{
		tok_next = tokens->next;
		printf("\n\n[%i] .%s%s%s. ", i++, BOLD, tokens->cmd, WHITE);
		print_type(tokens->type, 1);
		print_array(tokens->args, NULL);
		while (tokens->redir)
		{
			red_next = tokens->redir->next;
			printf("\n\tREDIR:\n\t -FD:%i \n\t -TYPE:", tokens->redir->fd);
			print_type(tokens->redir->type, 0);
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

void	print_array(char **array, char *type)
{
	int	i;

	i = -1;
	if (type)
		printf("\n%s%s>%s", RED, type, WHITE);
	while (array[++i])
	{
		printf("\n\t%i:%s%s%s$", i + 1, GREEN, array[i], WHITE);
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
