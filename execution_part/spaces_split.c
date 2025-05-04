/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spaces_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfellahi <sfellahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 13:09:09 by ilchahbi          #+#    #+#             */
/*   Updated: 2024/10/15 15:30:05 by sfellahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell1.h" 

size_t	count_words2(char const *s)
{
	size_t	count;
	int		is_word;

	count = 0;
	is_word = 0;
	while (*s)
	{
		if (!ft_isspace(*s) && !is_word)
		{
			is_word = 1;
			count++;
		}
		else if (ft_isspace(*s))
			is_word = 0;
		s++;
	}
	return (count);
}

static char	*extract_word2(char const *s)
{
	char	*word;
	size_t	len;

	len = 0;
	while (s[len] && !ft_isspace(s[len]))
		len++;
	word = (char *)malloc((len + 1) * sizeof(char));
	if (!word)
		return (NULL);
	len = 0;
	while (s[len] && !ft_isspace(s[len]))
	{
		word[len] = s[len];
		len++;
	}
	word[len] = '\0';
	return (word);
}

void	process_string2(char const *s, char **result, size_t *i)
{
	while (*s)
	{
		if (!ft_isspace(*s))
		{
			result[*i] = extract_word2(s);
			if (!result[*i])
			{
				free_split(result, *i);
				return ;
			}
			(*i)++;
			while (*s && !ft_isspace(*s))
				s++;
		}
		else
			s++;
	}
}

char	**ft_split_spaces(char const *s)
{
	char	**result;
	size_t	word_count;
	size_t	i;

	if (!s)
		return (NULL);
	word_count = count_words2(s);
	result = (char **)malloc((word_count + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	i = 0;
	process_string2(s, result, &i);
	result[i] = NULL;
	return (result);
}
