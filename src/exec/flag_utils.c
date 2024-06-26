/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorvarea <jorvarea@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 12:02:59 by jorvarea          #+#    #+#             */
/*   Updated: 2024/06/26 13:34:31 by jorvarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	char_in_str(char c, char *str)
{
	bool	found;
	int		i;

	found = false;
	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			found = true;
		i++;
	}
	return (found);
}

bool	valid_flag(char *flag, char *valid_flags)
{
	bool	valid;
	int		i;

	valid = true;
	if (flag[0] == '-' && flag[1])
	{
		i = 1;
		while (flag[i] && valid)
		{
			if (!char_in_str(flag[i], valid_flags))
				valid = false;
			i++;
		}
	}
	else
		valid = false;
	return (valid);
}

int	count_valid_flag_arg(char **args, char *valid_flags)
{
	bool	stop;
	int		count;
	int		i;

	stop = false;
	count = 0;
	i = 1;
	while (args[i] && !stop)
	{
		if (valid_flag(args[i], valid_flags))
			count++;
		else
			stop = true;
		i++;
	}
	return (count);
}

bool	found_flags(char **args)
{
	bool	found;

	found = false;
	if (args[1] && args[1][0] == '-' && args[1][1] != '-')
		found = true;
	return (found);
}

void	print_invalid_flag_error_msg(char *cmd, char invalid_flag, char *usage)
{
	ft_putstr_fd("-minishell: ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": -", STDERR_FILENO);
	ft_putchar_fd(invalid_flag, STDERR_FILENO);
	ft_putendl_fd(": invalid option", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": usage: ", STDERR_FILENO);
	ft_putendl_fd(usage, STDERR_FILENO);
}
