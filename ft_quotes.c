/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quotes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilchahbi <ilchahbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 03:09:04 by ilchahbi          #+#    #+#             */
/*   Updated: 2024/10/01 16:50:36 by ilchahbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_quote_mod(char *args)
{
	int	i;
	int	check;

	check = 0;
	i = 0;
	while (args[i])
	{
		if (args[i] == '\'' && check == 1)
			check = 0;
		else if (args[i] == '"' && check == 2)
			check = 0;
		else if (args[i] == '\'' && check == 0)
			check = 1;
		else if (args[i] == '"' && check == 0)
			check = 2;
		i++;
	}
	if (check != 0)
		return (0);
	return (1);
}

int	ft_strcmp1337(const char *s1, const char *s2)

{
	int	i;

	i = 0;
	if (!s1 || !s2)
		return (0);
	if (*s1 == '\0' && *s2 == '\0')
		return (0);
	while (s1[i] && s2[i] && s1[i] == s2[i])
	{
		i++;
	}
	return (s1[i] - s2[i]);
}

void	ft_strcpy1337(char *dst, const char *src)
{
	while (*src)
		*dst++ = *src++;
	*dst = '\0';
}
