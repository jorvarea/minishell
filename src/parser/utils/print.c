/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 14:54:05 by ana-cast          #+#    #+#             */
/*   Updated: 2024/06/24 18:14:25 by ana-cast         ###   ########.fr       */
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
