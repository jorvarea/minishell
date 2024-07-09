/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 15:39:41 by ana-cast          #+#    #+#             */
/*   Updated: 2024/07/09 20:36:35 by ana-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	memory_leak(char **result, int j)
{
	while (--j >= 0)
		free(result[j]);
	free(result);
}

static int	check_quotes(char const *s, int *i)
{
	int	check;

	if (s[*i] == '\'' || s[*i] == '\"')
	{
		check = ft_strchr(s + *i + 1, s[*i]) - (s + *i);
		if (check < 0 || !s[check])
		{
			*i += 1;
			return (0);
		}
		*i += check;
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
		while (ft_strchr(" \t", s[i]))
			i++;
		if (check_quotes(s, &i) >= 0)
			b_check = 0;
		else if (ft_strchr("()|&;", s[i]) && ++counter)
		{
			b_check = 0;
			if (ft_strchr("|&", s[i]) && s[i] == s[i + 1])
				i++;
		}
		else if (!b_check && ++counter)
			b_check = 1;
	}
	printf("\nWORD COUNT:%i\n", counter);
	return (counter);
}

static void	position_start_end(char const *s, int *start, int *end)
{
	while (s[*start] == ' ' || s[*start] == '\t')
		*start += 1;
	*end = *start;
	if (ft_strchr("()|&;", s[*start]))
	{
		*end += 1;
		if ((ft_strchr("|&", s[*start])) && s[*start] == s[*end])
			*end += 1;
	}
	else
	{
		while (s[*end] && !ft_strchr("()|&;", s[*end]))
		{
			if (check_quotes(s, end) == -1)
				*end += 1;
		}
	}
}

char	**trim_split(char **split, int len)
{
	char	**trim;
	int		i;

	trim = (char **)malloc(sizeof(char *) * len);
	i = -1;
	while (split[++i])
		trim[i] = ft_strtrim(split[i], " \t");
	trim[i] = NULL;
	free_array(&split);
	return (trim);
}

char	**split_input(char *input)
{
	char	**result;
	int		start;
	int		end;
	int		j;
	int		len;

	len = how_many(input) + 1;
	result = (char **)malloc(sizeof(char *) * len);
	if (!result || !input)
		return (NULL);
	start = 0;
	j = -1;
	while (input[start])
	{
		position_start_end(input, &start, &end);
		if (end > start)
		{
			result[++j] = ft_substr(input, start, end - start);
			if (!result[j])
				return (memory_leak(result, j), NULL);
			start = end;
		}
	}
	result[++j] = NULL;
	return (trim_split(result, len));
}