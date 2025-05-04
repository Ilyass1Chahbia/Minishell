/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils5.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilchahbi <ilchahbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 13:09:53 by ilchahbi          #+#    #+#             */
/*   Updated: 2024/09/20 13:09:53 by ilchahbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_delimiter(char c)
{
	return (c == 32 || (c >= 9 && c <= 13));
}

char	*get_prefix(const char *str, int n)
{
	if (n <= 0)
		return (NULL);
	return (ft_substr1337(str, 0, n));
}

int	skip_to_end(const char *str, int n)
{
	if (str[n])
		n++;
	while (str[n] && !is_delimiter(str[n]) && ft_isalnum1337(str[n]))
		n++;
	return (n);
}

char	*get_expansion(const char *str, int start, int end)
{
	return (ft_substr1337(str, start + 1, end - start - 1));
}

int	count_pipes(t_info *node)
{
	int	n;

	n = 0;
	while (node)
	{
		if (node->type == PIPE)
			n++;
		node = node->next;
	}
	return (n);
}
