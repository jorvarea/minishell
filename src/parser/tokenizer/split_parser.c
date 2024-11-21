/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 17:21:04 by ana-cast          #+#    #+#             */
/*   Updated: 2024/07/25 16:57:29 by ana-cast         ###   ########.fr       */
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
	while (++i < ft_strlen(s))
	{
		skip_quotes(s, &i);
		if (ft_strchr("();|><&", s[i]) && ++counter)
		{
			b_check = 0;
			if (ft_strchr("|><&", s[i]) && s[i] == s[i + 1])
				i++;
		}
		else if (ft_strchr(" \t\n\v\f\r", s[i]))
			b_check = 0;
		else if (!b_check && ++counter)
			b_check = 1;
	}
	return (counter);
}

static void	cmd_extract_string(char const *s, int *start, int *end)
{
	while (ft_strchr(" \t\n\v\f\r", s[*start]) && s[*start])
		*start += 1;
	*end = *start;
	if (ft_strchr("();|><& \t\n\v\f\r", s[*start]))
	{
		*end += 1;
		if ((ft_strchr("|><&", s[*start])) && s[*start] == s[*end])
			*end += 1;
	}
	else
	{
		while (s[*end] && !ft_strchr("();|><& \t\n\v\f\r", s[*end]))
		{
			skip_quotes(s, end);
			if (!ft_strchr("();|><& \t\n\v\f\r", s[*end]))
				*end += 1;
		}
	}
}

char	**trim_split(char **split, int len)
{
	char	**trim;
	int		i;

	trim = (char **)safe_malloc(sizeof(char *) * len);
	if (!trim)
		return (NULL);
	i = -1;
	while (split[++i])
		trim[i] = ft_strtrim(split[i], " \t\n\v\f\r");
	trim[i] = NULL;
	free_array(&split);
	return (trim);
}

char	**split_parser(char *input)
{
	char	**result;
	int		start;
	int		end;
	int		j;
	int		len;

	len = ft_strlen(input);
	result = (char **)safe_malloc(sizeof(char *) * (how_many(input) + 1));
	if (!result || !input)
		return (NULL);
	start = 0;
	j = -1;
	while (len > start)
	{
		cmd_extract_string(input, &start, &end);
		if (end > start && len > start)
		{
			result[++j] = ft_substr(input, start, end - start);
			if (!result[j])
				return (memory_leak(result, j), NULL);
		}
		start = end;
	}
	result[++j] = NULL;
	return (trim_split(result, how_many(input) + 1));
}
