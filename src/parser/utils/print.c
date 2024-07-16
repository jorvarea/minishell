/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 14:54:05 by ana-cast          #+#    #+#             */
/*   Updated: 2024/07/16 18:01:43 by ana-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	print_type(int type, int isToken)
{
	printf("%i->", type);
	if (type == 0 && isToken)
		printf("CMD");
	else if (type == 1 && isToken)
		printf ("AND");
	else if (type == 2 && isToken)
		printf ("OR");
	else if (type == 4 && isToken)
		printf ("PIPE");
	else if (type == 5 && isToken)
		printf ("OPEN PARENTHESIS");
	else if (type == 6 && isToken)
		printf ("CLOSE PARENTHESIS");
	else if (isToken)
		printf ("UNKNOWN");
	else if (type == 0)
		printf("INFILE");
	else if (type == 1)
		printf("APPEND");
	else if (type == 2)
		printf("OUTFILE");
	else if (type == 3)
		printf("HEREDOC");
}

void	print_command_list(t_cmd *tokens)
{
	t_cmd	*tok_next;
	t_redir	*red_next;
	int		i;

	i = 0;
	printf("\n%sCOMMAND LIST>%s\n", RED, WHITE);
	if (!tokens)
		printf("\t%s(null)%s\n\n", YELLOW, WHITE);
	while (tokens)
	{
		tok_next = tokens->next;
		printf("\n%sINDEX:%s%i", BOLD, WHITE, i++);
		printf("\t%sTYPE:%s", BOLD, WHITE);
		print_type(tokens->type, 1);
		print_array(tokens->args, tokens->cmd);
		while (tokens->redir)
		{
			red_next = tokens->redir->next;
			printf("%sREDIR:%s\n\tTYPE:", BOLD, WHITE);
			print_type(tokens->redir->type, 0);
			printf(" IN:%s\n", tokens->redir->file);
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
	printf("\n%s%s>%s\n", RED, type, WHITE);
	while (array[++i])
	{
		printf("\t%i:%s%s%s$\n", i + 1, GREEN, array[i], WHITE);
	}
}

void	print_shell(t_shell *shell, bool env, bool tokens)
{
	printf("\n%s%sPRINTING SHELL>%s\n", MAGENTA, BOLD, WHITE);
	printf("%sEXIT STATUS>%s %i\n", RED, WHITE, shell->exit_status);
	if (env)
	{
		print_array(shell->env, "CHAR **ENV");
		print_shell_l_env(shell->l_env);
	}
	if (tokens)
		print_command_list(shell->tokens);
}
