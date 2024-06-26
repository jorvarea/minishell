/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorvarea <jorvarea@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 22:39:34 by jorvarea          #+#    #+#             */
/*   Updated: 2024/06/27 00:06:35 by jorvarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	get_value(t_shell *shell, char *key, char *value, size_t value_size)
{
	t_env	*ptr;
	bool	found;

	found = false;
	ptr = shell->l_env;
	while (ptr && ptr->next)
	{
		if (ft_strncmp(ptr->key, key, ft_strlen(key)) == 0
			&& ft_strlen(ptr->value) < value_size)
		{
			found = true;
			ft_strlcpy(value, ptr->value, value_size);
		}
		ptr = ptr->next;
	}
	return (found);
}
