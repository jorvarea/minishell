/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorvarea <jorvarea@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 21:36:05 by jorvarea          #+#    #+#             */
/*   Updated: 2024/07/18 21:38:47 by jorvarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	safe_pipe(int *pipe_des)
{
	if (pipe(pipe_des) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
}
