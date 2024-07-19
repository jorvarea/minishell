/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 17:18:56 by ana-cast          #+#    #+#             */
/*   Updated: 2024/07/19 21:25:54 by ana-cast         ###   ########.fr       */
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

char	*process_input(char *str, t_shell *shell)
{
	int		i;
	int		j;
	char	*before;
	char	*after;
	int		quote_status;

	i = -1;
	while (str[++i])
	{
		j = i;
		quote_status = check_quotes(str, &i);
		if (quote_status == 2)
			return (ft_quotes_error(str, shell), NULL);
		else if (!quote_status)
		{
			before = ft_substr(str, 0, j);
			after = ft_substr(str, i + 1, ft_strlen(str));
			str = NULL;
			free(str);
			str = ft_strjoin(before, after);
			i = -1;
		}
	}
	return (str);
}

void	ft_quotes_error(const char *cmd, t_shell *shell)
{
	shell->exit_status = 127;
	ft_putstr_fd("-minishell: ", STDERR_FILENO);
	ft_putstr_fd((char *)cmd, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd("unclosed quotes", STDERR_FILENO);
}
