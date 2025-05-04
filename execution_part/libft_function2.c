/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_function2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilchahbi <ilchahbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 01:45:33 by sfellahi          #+#    #+#             */
/*   Updated: 2024/10/06 13:09:33 by ilchahbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell1.h"

int	find_word_end(const char *str, int i, char c)
{
	char	quote;

	quote = 0;
	while (str[i] && (str[i] != c || quote))
		i = handle_quotes11(str, i, &quote);
	return (i);
}

size_t	count_words(char const *s, char c)
{
	size_t	count;
	int		is_word;

	count = 0;
	is_word = 0;
	while (*s)
	{
		if (*s != c && !is_word)
		{
			is_word = 1;
			count++;
		}
		else if (*s == c)
			is_word = 0;
		s++;
	}
	return (count);
}

static char	*extract_word(char const *s, char c)
{
	char	*word;
	size_t	len;

	len = 0;
	while (s[len] && s[len] != c)
		len++;
	word = (char *)malloc((len + 1) * sizeof(char));
	if (!word)
		return (NULL);
	len = 0;
	while (s[len] && s[len] != c)
	{
		word[len] = s[len];
		len++;
	}
	word[len] = '\0';
	return (word);
}

void	process_string(char const *s, char c, char **result, size_t *i)
{
	while (*s)
	{
		if (*s != c)
		{
			result[*i] = extract_word(s, c);
			if (!result[*i])
			{
				free_split(result, *i);
				return ;
			}
			(*i)++;
			while (*s && *s != c)
				s++;
		}
		else
			s++;
	}
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	size_t	word_count;
	size_t	i;

	if (!s)
		return (NULL);
	word_count = count_words(s, c);
	result = (char **)malloc((word_count + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	i = 0;
	process_string(s, c, result, &i);
	result[i] = NULL;
	return (result);
}
