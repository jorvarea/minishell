/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_realloc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorvarea <jorvarea@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 22:13:34 by jorvarea          #+#    #+#             */
/*   Updated: 2024/07/24 17:57:09 by jorvarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**safe_realloc_array(char **array, size_t new_size)
{
	char	**new_array;
	int		i;

	if (array)
	{
		new_array = safe_malloc(new_size * sizeof(char *));
		i = 0;
		while (array[i])
		{
			new_array[i] = array[i];
			i++;
		}
		free(array);
	}
	else
		new_array = NULL;
	return (new_array);
}
