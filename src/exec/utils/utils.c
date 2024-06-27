/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorvarea <jorvarea@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 12:44:12 by jorvarea          #+#    #+#             */
/*   Updated: 2024/06/27 22:11:44 by jorvarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_words(char **ptr)
{
	int	i;

	i = 0;
	while (ptr[i])
		i++;
	return (i);
}

void	free_array_null(char ***array)
{
	int	i;

	i = -1;
	if (*array)
	{
		while ((*array)[++i])
			free((*array)[i]);
		free(*array);
		*array = NULL;
	}
}

bool	equal_str(char *s1, char *s2)
{
	int	len1;
	int	len2;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	return ((len1 == len2) && (ft_strncmp(s1, s2, len1) == 0));
}
