/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 20:28:08 by ana-cast          #+#    #+#             */
/*   Updated: 2024/05/17 20:50:32 by ana-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_parsed	*parser(char *input)
{
	t_parsed	*parsed_input;

	if (!input)
		return (NULL);
	parsed_input = (t_parsed *)malloc(sizeof(t_parsed));
	if (!parsed_input)
		return (NULL);
	return (parsed_input);
}
