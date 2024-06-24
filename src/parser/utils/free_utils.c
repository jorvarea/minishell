/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 14:05:01 by ana-cast          #+#    #+#             */
/*   Updated: 2024/06/24 15:10:00 by ana-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	sh_free_str(char *str)
{
	if (str)
	{
		str = NULL;	
		free(str);
	}
}

void	free_array(char **array)
{
	int	i;

	i = -1;
	if (array)
	{
		while (array[++i])
			free(array[i]);
		free(array);
		array = NULL;
	}
}

void	free_arg_lst(t_args *l_args)
{
	t_args	*next;

	while (l_args)
	{
		next = l_args->next;
		sh_free_str(l_args->arg);
		free(l_args);
		l_args = NULL;
		l_args = next;
		l_args->prev = NULL;
	}
}

void	free_redir(t_redir	*redir)
{
	t_redir	*next;

	while (redir)
	{
		next = redir->next;
		sh_free_str(redir->file);
		free(redir);
		redir = NULL;
		redir = next;
		redir->prev = NULL;
	}
}

void	free_env_list(t_env	*l_env)
{
	t_env	*next;

	while (l_env)
	{
		next = l_env->next;
		sh_free_str(l_env->key);
		sh_free_str(l_env->value);
		free(l_env);
		l_env = NULL;
		l_env = next;
		l_env->prev = NULL;
	}
}
