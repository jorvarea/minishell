/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_realloc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorvarea <jorvarea@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 22:13:34 by jorvarea          #+#    #+#             */
/*   Updated: 2024/07/18 22:24:02 by jorvarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*safe_realloc(void *ptr, size_t new_size, size_t old_size)
{
	void	*new_ptr;

	new_ptr = safe_malloc(new_size);
	if (ptr)
	{
		if (old_size <= new_size)
			ft_memcpy(new_ptr, ptr, old_size);
		else
			ft_memcpy(new_ptr, ptr, new_size);
	}
	free(ptr);
	return (new_ptr);
}
