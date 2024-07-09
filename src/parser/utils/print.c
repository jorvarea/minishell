/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 14:54:05 by ana-cast          #+#    #+#             */
/*   Updated: 2024/07/09 19:27:53 by ana-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	print_shell_env(char **env)
{
	while (*env)
		printf("%s\n", *env++);
}

void	print_shell_l_env(t_env *l_env)
{
	t_env	*next;
	int		i;

	i = 0;
	while (l_env)
	{
		next = l_env->next;
		printf("%i \n\tKEY:%s\n\tVALUE:%s\n", i++, l_env->key, l_env->value);
		l_env = next;
	}
}

void	print_array(char **array)
{
	int	i;

	i = -1;
	printf("PRINTING ARRAY:\n");
	while (array[++i])
	{
		printf("\t%i:%s%s%s$\n", i + 1, GREEN, array[i], WHITE);
	}
}

// void	print_command_lst(t_cmd *command_lst)
// {
// 	//t_cmd	*next;
// 	int		i;

// 	i = 0;
// 	//printf("hola\n\n\n");
// 	if (command_lst == NULL)
// 		printf("COMMAND LIST DOESNT EXIST");
// 	// while (command_lst)
// 	// {
// 	// 	next = command_lst->next;
// 	// 	printf("LST INDEX: %i", i++);
// 	// 	command_lst = next;
// 	// }
// }
