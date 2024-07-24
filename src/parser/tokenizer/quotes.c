/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 17:18:56 by ana-cast          #+#    #+#             */
/*   Updated: 2024/07/24 19:14:52 by ana-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	skip_quotes(char const *s, int *i)
{
	if (s[*i] == '\'' || s[*i] == '\"')
		*i += ft_strchr(s + *i + 1, s[*i]) - (s + *i);
	else
		return (NOT_QUOTE);
	return (CLOSED);
}

int	check_quotes(char const *s, int *i)
{
	int	check;

	if (s[*i] == '\'' || s[*i] == '\"')
	{
		check = ft_strchr(s + *i + 1, s[*i]) - (s + *i);
		if (check <= 1 || !s[check])
		{
			if (check <= 0)
				return (UNCLOSED);
			*i += 1;
			return (EMPTY);
		}
		*i += check;
	}
	else
		return (NOT_QUOTE);
	return (CLOSED);
}

int	only_space(char *s, int *start, int *end)
{
	int		i;
	char	c;

	c = s[*start];
	i = *start - 1;
	if (!ft_strchr("\'\"", c) || !(s[i] && ft_strchr(" \t", s[i])))
		return (0);
	while (++i <= *end)
	{
		if (s[i] != c && !ft_strchr(" \t", s[i]))
			return (0);
	}
	if (s[i] && !(s[i] && ft_strchr(" \t()|&;", s[i])))
		return (0);
	return (1);
}

char	*remove_empty_quotes(char *str, int end_s1, int start_s2)
{
	char	*s1;
	char	*s2;
	char	*join;

	s1 = ft_substr(str, 0, end_s1);
	s2 = ft_substr(str, start_s2, ft_strlen(str));
	join = ft_strjoin(s1, s2);
	free_str(&s1);
	free_str(&s2);
	free_str(&str);
	str = NULL;
	return (join);
}

char	*process_input(char *str, t_shell *shell)
{
	int		i;
	int		j;
	int		quote_status;

	i = -1;
	while (str[++i])
	{
		j = i;
		quote_status = check_quotes(str, &i);
		if (quote_status == 2)
		{
			free_str(&str);
			return (parser_error(E_UQUOTE, NULL, E_UQUOTE, shell));
		}
		else if (!quote_status)
		{
			str = remove_empty_quotes(str, j, i + 1);
			i = -1;
		}
	}
	return (str);
}
