/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 14:54:05 by ana-cast          #+#    #+#             */
/*   Updated: 2024/07/24 12:08:19 by ana-cast         ###   ########.fr       */
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

	if (!array || !array[0])
		printf("[%s%s(null)%s]", RED, BOLD, WHITE);
	else
	{
		len = array_len(array);
		if (title)
			printf("\n%s%s (len = %i)>%s\n", RED, title, len, WHITE);
		printf(" %s[%i]%s[", BOLD, len, WHITE);
		i = 0;
		while (i < len)
		{
			printf("%s%s%s,", GREEN, array[i], WHITE);
			i++;
		}
		printf("%s%i:(null)%s", BLUE, i, WHITE);
		printf("]");
		if (title)
			printf("\n");
	}
}

void	print_redir_type(int type)
{
	if (type == NOT_REDIR)
		printf("NOT REDIR(%i)", type);
	else if (type == INFILE)
		printf("INFILE(%i:\'<\')", type);
	else if (type == APPEND)
		printf("APPEND(%i:\'>>')", type);
	else if (type == OUTFILE)
		printf("OUTFILE(%i:\'>')", type);
	else if (type == HEREDOC)
		printf("HEREDOC(%i:\'<<')", type);
}

void	print_type(int type)
{
	if (type == 0)
		printf("-> CMD(%i)", type);
	else if (type == 1)
		printf ("-> AND(%i)", type);
	else if (type == 2)
		printf ("-> OR(%i)", type);
	else if (type == 4)
		printf ("-> PIPE(%i)", type);
	else if (type == 5)
		printf ("-> OPEN PARENTHESIS(%i)", type);
	else if (type == 6)
		printf ("-> CLOSE PARENTHESIS(%i)", type);
	else if (type == 7)
		printf ("-> REDIR(%i)", type);
	else
		printf ("-> UNKNOWN(%i)", type);
}
