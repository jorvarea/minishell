/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_input_print.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 15:39:41 by ana-cast          #+#    #+#             */
/*   Updated: 2024/07/10 15:28:55 by ana-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <minishell.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define WHITE "\033[0m"
#define BOLD "\033[1m"
#define GREEN "\033[0;32m"
#define RED "\033[0;31m"
#define BLUE "\033[0;34m"
#define YELLOW "\033[33m"
#define MAGENTA "\033[35m"
#define TURQUOISE "\033[36m"

void	free_array(char ***array);
void	print_array(char **array);
char	*ft_strchr(const char *s, int c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strtrim(char const *s1, char const *set);

static void	memory_leak(char **result, int j)
{
	while (--j >= 0)
		free(result[j]);
	free(result);
}

static int	check_quotes(char const *s, int *i)
{
	int	check;

	if (s[*i] == '\'' || s[*i] == '\"')
	{
		check = ft_strchr(s + *i + 1, s[*i]) - (s + *i);
		if (check < 0 || !s[check])
		{
			*i += 1;
			return (0);
		}
		*i += check;
	}
	else
		return (-1);
	return (1);
}

static int	how_many(char const *s)
{
	int	i;
	int	counter;
	int	b_check;
	int	check_counter;
	int	check_i;

	check_counter = 0;
	check_i = 0;
	i = -1;
	counter = 0;
	b_check = 0;
	while (s[++i])
	{
		if (check_counter != counter)
		{
			if (check_counter)
				printf("<\n");
			printf("COUNTER: %i->%i\n>", check_counter, counter);
		}
		check_counter = counter;
		while (check_i < i)
			printf("%c", s[check_i++]);
		while (ft_strchr(" \t", s[i]))
			i++;
		if (ft_strchr("()|&;", s[i]) && ++counter)
		{
			b_check = 0;
			if (ft_strchr("|&", s[i]) && s[i] == s[i + 1])
				i++;
		}
		else if (check_quotes(s, &i) >= 0 && b_check)
			;
		else if (!b_check && ++counter)
			b_check = 1;
	}
	if (check_counter != counter)
			printf("<\nCOUNTER CHANGED: %i->%i\n>", check_counter, counter);
	while (check_i < i)
		printf("%c", s[check_i++]);
	printf("\nWORD COUNT:%i\n", counter);
	return (counter);
}

static void	position_start_end(char const *s, int *start, int *end)
{
	while (s[*start] == ' ' || s[*start] == '\t')
		*start += 1;
	*end = *start;
	if (ft_strchr("()|&;", s[*start]))
	{
		*end += 1;
		if ((ft_strchr("|&", s[*start])) && s[*start] == s[*end])
			*end += 1;
	}
	else
	{
		while (s[*end] && !ft_strchr("()|&;", s[*end]))
		{
			if (check_quotes(s, end) == -1)
				*end += 1;
		}
	}
}

char	**trim_split(char **split, int len)
{
	char	**trim;
	int		i;

	trim = (char **)malloc(sizeof(char *) * len);
	i = -1;
	while (split[++i])
		trim[i] = ft_strtrim(split[i], " \t");
	trim[i] = NULL;
	free_array(&split);
	return (trim);
}

char	**split_input(char *input)
{
	char	**result;
	int		start;
	int		end;
	int		j;
	int		len;

	len = how_many(input) + 1;
	result = (char **)malloc(sizeof(char *) * len);
	if (!result || !input)
		return (NULL);
	start = 0;
	j = -1;
	while (input[start])
	{
		position_start_end(input, &start, &end);
		if (end > start)
		{
			result[++j] = ft_substr(input, start, end - start);
			if (!result[j])
				return (memory_leak(result, j), NULL);
			start = end;
		}
	}
	result[++j] = NULL;
	return (trim_split(result, len));
}

int	main(void)
{
	char	**commands;
	char	*str;

	//str = "echo \"hola a\" \" || (echo todo bien && echo jij && echo jaj)";
	commands = split_input(str);
	printf("\n%s%s%s\n", MAGENTA, str, WHITE);
	print_array(commands);
	free_array(&commands);
}

void	free_array(char ***array)
{
	int	i;

	i = -1;
	if (*array)
	{
		while ((*array)[++i])
			free((*array)[i]);
		free(*array);
		*array = NULL;
	}
}

void	print_array(char **array)
{
	int	i;

	i = -1;
	printf("PRINTING ARRAY:\n");
	while (array[++i])
	{
		printf("\t%i:%s%s%s$\n", i + 1, GREEN, array[i], WHITE);
	}
}

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while ((char)s[i])
	{
		if (s[i] == (char)c)
			return (&((char *)s)[i]);
		i++;
	}
	if ((char)c == '\0')
		return (&((char *)s)[i]);
	return (0);
}

int	ft_strlen(const char *str)
{
	int	count;

	count = 0;
	while (str[count])
		count++;
	return (count);
}

char	*ft_strdup(char *s1)
{
	char	*dest;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (s1[i])
		i++;
	dest = (char *)malloc(sizeof(char) * (i + 1));
	if (dest == NULL)
		return (NULL);
	while (s1[j])
	{
		dest[j] = s1[j];
		j++;
	}
	dest[j] = '\0';
	return (dest);
}

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
	substr = (char *)malloc(sizeof(char) * len + 1);
	if (!substr)
		return (NULL);
	i = -1;
	while (++i < (unsigned int)len)
		substr[i] = s[start + i];
	substr[i] = '\0';
	return (substr);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		end;
	char	*trim;

	start = 0;
	while (ft_strchr(set, s1[start]) && s1[start])
		start++;
	end = ft_strlen((char *)s1) - 1;
	while (ft_strchr(set, s1[end]))
		end--;
	trim = ft_substr(s1, start, end - start + 1);
	return (trim);
}
