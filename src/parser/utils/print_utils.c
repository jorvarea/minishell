/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 14:54:05 by ana-cast          #+#    #+#             */
/*   Updated: 2024/07/20 21:27:50 by ana-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	print_array(char **array, char *type)
{
	int	i;

	i = -1;
	if (type)
		printf("\n%s%s>%s", RED, type, WHITE);
	while (array[++i])
		printf("\n\t%i:%s%s%s$", i + 1, GREEN, array[i], WHITE);
}

void	print_array_one_line(char **array, char *title)
{
	int		len;
	int		i;

	len = array_len(array);
	if (title)
		printf("\n%s%s (len = %i)>%s\n", RED, title, len, WHITE);
	printf(" [");
	i = 0;
	while (i < len)
	{
		printf("%s%s%s,", GREEN, array[i], WHITE);
		i++;
	}
	if (i == 0)
		printf("%s%s", RED, BOLD);
	else
		printf("%s", BLUE);
	printf("%i:%s%s", i, array[i], WHITE);
	printf("]");
	if (title)
		printf("\n");
}
