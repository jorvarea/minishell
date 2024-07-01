/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strinsert.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorvarea <jorvarea@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 15:10:57 by jorvarea          #+#    #+#             */
/*   Updated: 2024/07/01 15:25:30 by jorvarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strinsert(char *str, char *insertion, int index)
{
	char	*new_str;
	int		len_insertion;
	int		len_str;
	int		i;
	int		j;

	if (!str || !insertion)
		return (NULL);
	len_insertion = ft_strlen(insertion);
	len_str = ft_strlen(str);
	new_str = (char *)malloc(len_str + len_insertion + 1);
	if (!new_str)
		return (NULL);
	i = 0;
	while (i < index)
	{
		new_str[i] = str[i];
		i++;
	}
	j = 0;
	while (j < len_insertion)
	{
		new_str[i + j] = insertion[j];
		j++;
	}
	while (i < len_str)
	{
		new_str[i + len_insertion] = str[i];
		i++;
	}
	new_str[len_str + len_insertion] = '\0';
	return (new_str);
}
