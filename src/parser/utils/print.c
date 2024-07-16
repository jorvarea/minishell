/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 14:54:05 by ana-cast          #+#    #+#             */
/*   Updated: 2024/07/16 16:10:18 by ana-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	print_command_list(t_cmd *tokens)
{
	t_cmd	*tok_next;
	t_redir	*red_next;
	int		i;

	i = 0;
	printf("\n%sT_CMD	*TOKENS>%s\n", RED, WHITE);
	if (!tokens)
		printf("\t%s(null)%s\n\n", YELLOW, WHITE);
	while (tokens)
	{
		tok_next = tokens->next;
		printf("%sINDEX:%s%i\n", BOLD, WHITE, i++);
		printf("%sTYPE:%s%u\n", BOLD, WHITE, tokens->type);
		print_array(tokens->args, tokens->cmd);
		while (tokens->redir)
		{
			red_next = tokens->redir->next;
			printf("%sREDIR:%s\n\t", BOLD, WHITE);
			printf("TYPE:%i IN:%s\n", tokens->redir->type, tokens->redir->file);
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
