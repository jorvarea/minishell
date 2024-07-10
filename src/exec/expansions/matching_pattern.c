/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matching_pattern.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorvarea <jorvarea@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 14:43:50 by jorvarea          #+#    #+#             */
/*   Updated: 2024/07/10 15:02:13 by jorvarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	all_equal(char *str, char c)
{
	bool	equal;
	int		i;

	equal = true;
	i = 0;
	while (str[i] && equal)
	{
		if (str[i] != c)
			equal = false;
		i++;
	}
	return (equal);
}

bool	matching_pattern(char *pattern, char *str)
{
	int	p_idx;
	int	s_idx;
	int	next2wildcard_idx;

	p_idx = 0;
	s_idx = 0;
	next2wildcard_idx = -1;
	while (str[s_idx])
	{
		if (pattern[p_idx] == str[s_idx])
		{
			p_idx++;
			s_idx++;
		}
		else if (pattern[p_idx] == '*')
			next2wildcard_idx = ++p_idx;
		else if (next2wildcard_idx != -1)
		{
			p_idx = next2wildcard_idx;
			s_idx++;
		}
		else
			return (false);
	}
	return (pattern[p_idx] == '\0' || all_equal(&pattern[p_idx], '*'));
}
