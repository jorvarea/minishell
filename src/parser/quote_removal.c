/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_removal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 12:50:41 by ana-cast          #+#    #+#             */
/*   Updated: 2024/07/25 16:22:05 by ana-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	remove_quotes(char **quotes, int start, int end)
{
	char	*before;
	char	*inside;
	char	*join;

	before = ft_substr(*quotes, 0, start);
	inside = ft_substr(*quotes, start + 1, (end - 1) - start);
	join = ft_strjoin(inside, *quotes + (end + 1));
	free_str(quotes);
	*quotes = ft_strjoin(before, join);
	free_str(&inside);
	free_str(&before);
	free_str(&join);
}

void	remove_str_quotes(char **str)
{
	int		i;
	int		q_end;

	i = -1;
	while ((*str)[++i])
	{
		q_end = i + 1;
		if (ft_strchr("\"\'", (*str)[i]))
		{
			while ((*str)[i] && (*str)[i] != (*str)[q_end])
				q_end++;
			remove_quotes(str, i, q_end);
			i = -1;
		}
	}
}

void	remove_array_quotes(char **array)
{
	int		i;

	i = -1;
	while (++i < array_len(array) && array[i])
		remove_str_quotes(&array[i]);
}

// void	remove_all_quotes(t_cmd *tokens)
// {
// 	t_cmd	*node;
// 	int		i;

// 	node = tokens;
// 	while (node)
// 	{
// 		i = -1;
// 		remove_array_quotes(node->args);
// 		node = node->next;
// 	}
// }
