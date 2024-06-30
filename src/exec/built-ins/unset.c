/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorvarea <jorvarea@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 21:52:17 by jorvarea          #+#    #+#             */
/*   Updated: 2024/06/30 12:55:03 by jorvarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unset(t_shell *shell, char **args)
{
	int	i;

	if (found_flags(args))
		ft_invalid_flag_error(shell, "unset", args[1][1],
			"unset [name ...]");
	else
	{
		i = 1;
		while (args[i]) 
			remove_key(shell, args[i++]);
	}
}
