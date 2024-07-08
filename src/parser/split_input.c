/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 17:21:04 by ana-cast          #+#    #+#             */
/*   Updated: 2024/07/08 19:24:53 by ana-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	memory_leak(char **result, int j)
{
	while (--j >= 0)
		free(result[j]);
	free(result);
}

static int	how_many(char const *s)
{
	int	i;
	int	counter;
	int	b_check;

	i = -1;
	counter = 0;
	b_check = 0; 
	while (s[++i])
	{
		if (ft_strchr("|><&;\'\"", s[i]) && ++counter)
		{
			b_check = 0;
			if (s[i] == '\'' || s[i] == '\"') 
				i += ft_strchr(s + i + 1, s[i]) - (s + i);
			else if (s[i] != ';' && s[i] == s[i + 1])
				i++;
		}
		else if (s[i] != ' ' && s[i] != '\t' && (!b_check && ++counter))
				b_check = 1;
		else if (ft_strchr(" \t", s[i]))
			b_check = 0;
	}
	return (counter);
}

static void	position_start_end(char const *s, int *start, int *end)
{
	while (s[*start] == ' ' || s[*start] == '\t')
		*start += 1;
	*end = *start;
	if (s[*start] == '\'' || s[*start] == '\"')
		*end += ft_strchr(s + *start + 1, s[*start]) - (s + *start) + 1;
	else if (ft_strchr("|><&; ", s[*start]))
	{
		*end += 1;
		if ((ft_strchr("|><&", s[*start])) && s[*start] == s[*end])
			*end += 1;
	}
	else 
	{
		while (s[*end] && !ft_strchr("| \'\"><&;", s[*end]))
			*end += 1;
	}
}

char	**split_input(char *input)
{
	char	**result;
	int		start;
	int		end;
	int		j;

	result = (char **)malloc(sizeof(char *) * (how_many(input) + 1));
	if (!result || !input)
		return (NULL);
	start = 0;
	j = 0;
	while (input[start])
	{
		position_start_end(input, &start, &end);
		if (end > start) 
		{
			result[j] = ft_substr(input, start, end - start);
			if (!result[j])
				return (memory_leak(result, j), NULL);
			start = end;
			j++;
		}
	}
	result[j] = NULL;
	return (result);
}
