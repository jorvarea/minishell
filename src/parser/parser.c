/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 20:28:08 by ana-cast          #+#    #+#             */
/*   Updated: 2024/06/24 19:33:54 by ana-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*
	FUNCIONALIDAD: 
	Convertir input en lista de comandos. Teniendo en cuenta: 
		- argumentos, redirecciones y pipes

	PASOS: 
		- Crear + init command_lst y node
		- Dividir input en tokens (tokenizar)
		- Parsear tokens (while tokens...)
			- Crear comandos a partir de los tokens (init? mirar redirecciones)
			- 1st cmd
			- manejar pipe si es necesario (crear sig comando etc ?)
*/
t_cmd	*parser(char *input, t_shell *shell)
{
	t_cmd	*command_lst;
	size_t	num_cmd;

	(void)shell;
	if (!input)
		return (NULL);
	num_cmd = command_counter(input);
	split_input(input);
	printf("Input: %s\nNodes in command_lst: %zu\n", input, num_cmd);
	command_lst = (t_cmd *)malloc(sizeof(t_cmd));
	if (!command_lst)
		return (NULL);
	return (command_lst);
}

char	**trim_input(char **input)
{
	char	*trim;
	int		i;

	i = -1;
	while (input[++i])
	{
		trim = ft_strtrim(input[i], " \t"); // finish chars to trim
		sh_free_str(input[i]);
		input[i] = trim;
	}
	return (input);
}

char	**split_input(char *input)
{
	char	**input_split;
	char	**input_trimmed;

	input_split = ft_split(input, '"');
	input_trimmed = trim_input(input_split);
	if (!input_split)
		return (NULL);
	print_array(input_split);
	free_array(input_split);
	return (NULL);
}

size_t	command_counter(char *input)
{
	int		i;
	size_t	n;

	i = 0;
	n = 0;
	while (input[i])
	{
		i++;
	}
	return (n);
}
