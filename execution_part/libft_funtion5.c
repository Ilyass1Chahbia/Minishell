/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_funtion5.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfellahi <sfellahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 22:35:45 by sfellahi          #+#    #+#             */
/*   Updated: 2024/09/27 11:05:26 by sfellahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell1.h"

int	ft_atoi(const char *str)
{
	int				i;
	unsigned long	result;
	int				sign;

	i = 0;
	result = 0;
	sign = 1;
	while ((str[i] != '\0' && (str[i] >= 9 && str[i] <= 13)) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -sign;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (((result * 10) + (str[i] - '0')) > 9223372036854775807)
			return (check(sign));
		result = (result * 10) + (str[i] - '0');
		i++;
	}
	return (result * sign);
}

size_t	strlenbysaad(const char *s)
{
	size_t	j;

	j = 0;
	while (*(s + j) != '\0')
	{
		j++;
	}
	return (j);
}

size_t	char_check(char const *str, char const c)
{
	size_t	i;

	if (!str)
		return (0);
	i = 0;
	while (*(str + i))
	{
		if (*(str + i) == c)
			return (1);
		i++;
	}
	return (0);
}

int	check(int a)
{
	if (a < 0)
		return (0);
	return (-1);
}
