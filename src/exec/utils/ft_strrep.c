/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorvarea <jorvarea@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 15:10:57 by jorvarea          #+#    #+#             */
/*   Updated: 2024/07/24 17:44:57 by jorvarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Replaces a substring within a string with a new substring.
 *
 * Removes characters from start_index to end_index (not included)
 * in the original string and inserts the replacement string in their place.
 *
 * @param str The original string.
 * @param insertion The string to insert.
 * @param start_index The start index of the substring to be replaced.
 * @param end_index The end index (exclusive) of the substring to be replaced.
 * @return A newly allocated string with the replacement, or NULL on error.
 */
char	*ft_strrep(char *str, char *insertion, int start_index, int end_index)
{
	char	*new_str;
	int		len_insertion;
	int		len_str;
	int		i;

	len_insertion = ft_strlen(insertion);
	len_str = ft_strlen(str);
	if (!str || !insertion || start_index > end_index || start_index >= len_str
		|| end_index > len_str)
		return (NULL);
	new_str = (char *)safe_malloc(len_str - (end_index - start_index)
			+ len_insertion + 1);
	i = -1;
	while (++i < start_index)
		new_str[i] = str[i];
	i = -1;
	while (++i < len_insertion)
		new_str[start_index + i] = insertion[i];
	i = -1;
	while (str[end_index + ++i])
		new_str[start_index + len_insertion + i] = str[end_index + i];
	new_str[len_insertion + len_str - (end_index - start_index)] = '\0';
	return (new_str);
}
