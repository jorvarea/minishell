/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 18:21:41 by ana-cast          #+#    #+#             */
/*   Updated: 2024/03/05 18:35:46 by ana-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	i;
	char			*substr;
	unsigned int	s_len;

	if (!s)
		return (NULL);
	s_len = (unsigned int)ft_strlen((char *)s);
	if (start >= s_len)
		return (ft_strdup(""));
	if (start + len > s_len)
		len = s_len - start;
	substr = (char *)safe_malloc(sizeof(char) * len + 1);
	if (!substr)
		return (NULL);
	i = -1;
	while (++i < (unsigned int)len)
		substr[i] = s[start + i];
	substr[i] = '\0';
	return (substr);
}
