/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorvarea <jorvarea@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 21:07:21 by ana-cast          #+#    #+#             */
/*   Updated: 2024/06/26 13:22:51 by jorvarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	echo(char **args)
{
	bool	no_newline_flag;
	int		i;

	i = count_valid_flag_arg(args, "n") + 1;
	no_newline_flag = false;
	if (i > 1 && char_in_str('n', args[1]))
		no_newline_flag = true;
	while (args[i])
	{
		ft_putstr_fd(args[i], STDOUT_FILENO);
		if (args[i + 1])
			ft_putstr_fd(" ", STDOUT_FILENO);
		i++;
	}
	if (!no_newline_flag)
		ft_putstr_fd("\n", STDOUT_FILENO);
}
