/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wildcards.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorvarea <jorvarea@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 17:11:40 by jorvarea          #+#    #+#             */
/*   Updated: 2024/07/24 17:55:04 by jorvarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	add_arg(t_args_array *new_args, char *new_arg)
{
	if (new_args->n_args >= new_args->maximum_size - 1)
	{
		new_args->args = safe_realloc_array(new_args->args, 2
				* new_args->maximum_size);
		new_args->maximum_size *= 2;
	}
	new_args->args[new_args->n_args++] = ft_strdup(new_arg);
	new_args->args[new_args->n_args] = NULL;
}

static void	replace_wildcard(char *arg, t_args_array *new_args)
{
	struct dirent	*dir_entry;
	DIR				*dirp;

	dirp = opendir(".");
	if (dirp)
	{
		dir_entry = readdir(dirp);
		while (dir_entry)
		{
			if (dir_entry->d_name[0] != '.' && matching_pattern(arg,
					dir_entry->d_name))
				add_arg(new_args, dir_entry->d_name);
			dir_entry = readdir(dirp);
		}
		closedir(dirp);
	}
}

static bool	contains_wildcard(char *arg)
{
	bool	single_quotes;
	bool	double_quotes;
	bool	wildcard;
	int		i;

	single_quotes = false;
	double_quotes = false;
	wildcard = false;
	i = 0;
	while (arg[i] && !wildcard)
	{
		if (arg[i] == '\'')
			single_quotes = !single_quotes;
		else if (arg[i] == '\"')
			double_quotes = !double_quotes;
		else if (arg[i] == '*' && !single_quotes && !double_quotes)
			wildcard = true;
		i++;
	}
	return (wildcard);
}

void	expand_wildcards_cmd(t_cmd *cmd)
{
	t_args_array	new_args;
	char			**args;
	int				i;

	args = cmd->args;
	new_args.maximum_size = count_words(args) * 2;
	new_args.n_args = 0;
	new_args.args = safe_malloc(new_args.maximum_size * sizeof(char *));
	i = 0;
	while (args[i])
	{
		if (contains_wildcard(args[i]))
			replace_wildcard(args[i], &new_args);
		else
			add_arg(&new_args, args[i]);
		i++;
	}
	new_args.args[new_args.n_args] = NULL;
	free_array(&cmd->args);
	cmd->args = new_args.args;
}
