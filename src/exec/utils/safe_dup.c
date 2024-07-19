/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_dup.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorvarea <jorvarea@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 19:59:57 by jorvarea          #+#    #+#             */
/*   Updated: 2024/07/19 20:04:15 by jorvarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	safe_dup(int fd)
{
	int	dup_fd;

	dup_fd = dup(fd);
	if (dup_fd == -1)
	{
		perror("dup");
		exit(EXIT_FAILURE);
	}
	return (dup_fd);
}
