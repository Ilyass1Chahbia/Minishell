/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilchahbi <ilchahbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 13:21:27 by sfellahi          #+#    #+#             */
/*   Updated: 2024/10/06 12:10:01 by ilchahbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell1.h"

static int	is_in_quotes(char c, int *in_quotes, char *quote_char)
{
	if (c == '"' || c == '\'')
	{
		if (*in_quotes && *quote_char == c)
			*in_quotes = 0;
		else if (!*in_quotes)
		{
			*in_quotes = 1;
			*quote_char = c;
		}
		return (1);
	}
	return (0);
}

static int	is_heredoc_start(char *read, int in_quotes)
{
	return (!in_quotes && read[0] == '<' && read[1] == '<');
}

static void	skip_heredocs(char **read)
{
	*read += 2;
	while (**read && **read != ' ' && **read != '\t')
		(*read)++;
}

void	process_characters(char **read, char **write,
	int *in_quotes, char *quote_char)
{
	if (!is_in_quotes(**read, in_quotes, quote_char))
	{
		if (is_heredoc_start(*read, *in_quotes))
		{
			skip_heredocs(read);
			return ;
		}
		**write = **read;
		(*write)++;
	}
	(*read)++;
}
