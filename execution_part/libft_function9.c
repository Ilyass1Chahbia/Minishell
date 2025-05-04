/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_function9.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfellahi <sfellahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 10:37:20 by sfellahi          #+#    #+#             */
/*   Updated: 2024/09/27 10:48:37 by sfellahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell1.h"

int	skip_spaces(const char *str, int i, char c)
{
	while (str[i] == c)
		i++;
	return (i);
}

int	handle_quotes11(const char *str, int i, char *quote)
{
	if (str[i] == '\'' || str[i] == '\"')
	{
		if (!*quote)
			*quote = str[i];
		else if (str[i] == *quote)
			*quote = 0;
	}
	return (i + 1);
}
