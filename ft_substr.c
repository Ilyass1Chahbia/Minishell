/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilchahbi <ilchahbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 11:10:40 by ilchahbi          #+#    #+#             */
/*   Updated: 2024/09/09 15:01:47 by ilchahbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*ft_calloc1337(size_t count, size_t size)
{
	unsigned char	*array;
	size_t			l;
	size_t			i;

	i = 0;
	l = count * size;
	array = (void *)mark_sweep(NULL, l, -1);
	if (!array)
		return (0);
	while (i < l)
	{
		array[i] = 0;
		i++;
	}
	return (array);
}

char	*ft_substr1337(char const *s, int start, int len)
{
	int				i;
	int				s_len;
	char			*substr;

	if (len == 0)
		return (NULL);
	s_len = ft_strlen(s);
	if (s_len <= start || len == 0)
	{
		substr = ft_calloc1337(1, sizeof(char));
		return (substr);
	}
	if (len > ft_strlen(s + start))
		len = ft_strlen(s + start);
	substr = mark_sweep(NULL, (sizeof(char) * (len + 1)), -1);
	if (!(substr))
		return (NULL);
	i = 0;
	while (i < len)
	{
		substr[i] = s[start + i];
		i++;
	}
	substr[i] = '\0';
	return (substr);
}

void	ft_itoa_utils(char *result, int nbr, int len)
{
	if (nbr == 0)
	{
		result[0] = '0';
	}
	if (nbr < 0)
	{
		result[0] = '-';
		nbr = -nbr;
	}
	while (nbr)
	{
		result[--len] = nbr % 10 + '0';
		nbr /= 10;
	}
}

char	*ft_itoa2(int nbr)
{
	int		n;
	int		len;
	char	*result;

	if (nbr == -2147483648)
		return ("-2147483648\0");
	n = nbr;
	len = 0;
	if (nbr <= 0)
		len++;
	while (n)
	{
		n /= 10;
		len++;
	}
	result = (char *)mark_sweep(NULL, (sizeof(char) * (len + 1)), -1);
	if (result == NULL)
		return (NULL);
	ft_itoa_utils(result, nbr, len);
	result[len] = '\0';
	return (result);
}
