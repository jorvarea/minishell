/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 20:28:08 by ana-cast          #+#    #+#             */
/*   Updated: 2024/06/19 19:52:32 by ana-cast         ###   ########.fr       */
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
t_cmd	*parser(char *input)
{
	t_cmd	*command_lst;

	if (!input)
		return (NULL);
	command_lst = (t_cmd *)malloc(sizeof(t_cmd));
	if (!command_lst)
		return (NULL);
	return (command_lst);
}
