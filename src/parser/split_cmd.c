/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 17:21:04 by ana-cast          #+#    #+#             */
/*   Updated: 2024/07/09 20:02:22 by ana-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	memory_leak(char **result, int j)
{
	while (--j >= 0)
		free(result[j]);
	free(result);
}

static int	check_quotes(char const *s, int *start, int *end)
{
	int	i;

	if (s[*start] == '\'' || s[*start] == '\"')
	{
		i = ft_strchr(s + *start + 1, s[*start]) - (s + *start) + 1;
		if (i < 0 || !s[i])
		{
			*start += 1;
			*end = *start;
			return (0);
		}
		*end += i;
	}
	else
		return (-1);
	return (1);
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
		if (ft_strchr("()|><&;\'\"", s[i]) && ++counter)
		{
			b_check = 0;
			if (!check_quotes(s, &i, &i))
				counter--;
			else if (!ft_strchr("();", s[i]) && s[i] == s[i + 1])
				i++;
		}
		else if (s[i] != ' ' && s[i] != '\t' && (!b_check && ++counter))
			b_check = 1;
		else if (ft_strchr(" \t", s[i]))
			b_check = 0;
	}
	printf("TOTAL WORDS SPLIT: %i\n", counter);
	return (counter);
}

static void	position_start_end(char const *s, int *start, int *end)
{
	while (s[*start] == ' ' || s[*start] == '\t')
		*start += 1;
	*end = *start;
	if (check_quotes(s, start, end) > 0)
		;
	else if (ft_strchr("()|><&; ", s[*start]))
	{
		*end += 1;
		if ((ft_strchr("()|><&", s[*start])) && s[*start] == s[*end])
			*end += 1;
	}
	else
	{
		while (s[*end] && !ft_strchr("()| \'\"><&;", s[*end]))
			*end += 1;
	}
}

char	**split_cmd(char *input)
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
