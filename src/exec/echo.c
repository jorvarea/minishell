/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorvarea <jorvarea@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 21:07:21 by ana-cast          #+#    #+#             */
/*   Updated: 2024/06/26 00:54:17 by jorvarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static bool	char_in_str(char c, char *str)
{
	bool	found;
	int		i;

	found = false;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			found = true;
		i++;
	}
	return (found);
}

static bool	valid_flag(char *flag, char *valid_flags)
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

static int	count_flag_arg(char **args, char *valid_flags,
		bool *no_newline_flag)
{
	bool	stop;
	int		count;
	int		i;

	*no_newline_flag = false;
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
	if (count > 0 && char_in_str('n', args[1]))
		*no_newline_flag = true;
	return (count);
}

void	echo(char **args)
{
	bool	no_newline_flag;
	int		i;

	i = count_flag_arg(args, "n", &no_newline_flag) + 1;
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
