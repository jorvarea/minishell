/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 20:28:08 by ana-cast          #+#    #+#             */
/*   Updated: 2024/07/16 12:31:17 by ana-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	check_quotes(char const *s, int *i)
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

static int	only_space(char *s, int *start, int *end)
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
	if (s[i] && !(s[i] && ft_strchr(" \t", s[i])))
		return (0);
	return (1);
}

char	*remove_empty_quotes(char *str, t_shell *shell)
{
	int		i;
	int		j;
	char	*before;
	char	*after;
	int		quote_status;

	i = 0;
	while (str[i])
	{
		j = i;
		quote_status = check_quotes(str, &i);
		if (quote_status == 2)
			return (ft_quotes_error(str, shell), NULL);
		else if (!quote_status || only_space(str, &j, &i))
		{
			before = ft_substr(str, 0, j);
			after = ft_substr(str, i + 1, ft_strlen(str));
			str = NULL;
			free(str);
			str = ft_strjoin(before, after);
			i = -1;
		}
		i++;
	}
	return (str);
}

t_cmd	*parser(char *input, t_shell *shell)
{
	t_cmd	*command_lst;
	char	**commands;
	char	**input_array;
	int		i;

	(void)shell;
	i = -1;
	input = remove_empty_quotes(input, shell);
	if (!input)
		return (NULL);
	printf("%sINPUT>%s ", RED, WHITE);
	input_array = split_input(input);
	if (!input_array)
		return (NULL);
	print_array(input_array);
	printf("\n%sCOMMANDS>%s ", RED, WHITE);
	while (input_array[++i])
	{
		commands = split_cmd(input_array[i]);
		print_array(commands);
		free_array(&commands);
	}
	free_array(&input_array);
	command_lst = (t_cmd *)malloc(sizeof(t_cmd));
	if (!command_lst)
		return (NULL);
	return (command_lst);
}
