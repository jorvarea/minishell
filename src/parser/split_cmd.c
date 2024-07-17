/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 17:21:04 by ana-cast          #+#    #+#             */
/*   Updated: 2024/07/17 13:20:37 by ana-cast         ###   ########.fr       */
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
		if (ft_strchr("()|><&;", s[i]) && ++counter)
		{
			b_check = 0;
			if (!ft_strchr("();", s[i]) && s[i] == s[i + 1])
				i++;
		}
		else if (s[i] != ' ' && s[i] != '\t' && (!b_check && ++counter))
			b_check = 1;
		else if (ft_strchr(" \t", s[i]))
			b_check = 0;
	}
	//printf("\nWORD COUNT:%i\n", counter);
	return (counter);
}

static void	cmd_extract_string(char const *s, int *start, int *end)
{
	while (ft_strchr(" \t\n\v\f\r", s[*start]))
		*start += 1;
	*end = *start;
	if (!*start)
		;
	if (ft_strchr(">< ", s[*start]))
	{
		*end += 1;
		if ((ft_strchr("><", s[*start])) && s[*start] == s[*end])
			*end += 1;
	}
	else
	{
		while (s[*end] && !ft_strchr(">< ", s[*end]))
		{
			skip_quotes(s, end);
			if (!ft_strchr(">< ", s[*end]))
				*end += 1;
		}
	}
}

char	**split_cmd(char *input)
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
		cmd_extract_string(input, &start, &end);
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
