/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_function6.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilchahbi <ilchahbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 14:12:07 by sfellahi          #+#    #+#             */
/*   Updated: 2024/10/06 12:27:40 by ilchahbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell1.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*trim;
	size_t	start;
	size_t	end;
	size_t	i;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	while (*(s1 + start) && char_check(set, *(s1 + start)))
		start++;
	end = strlenbysaad(s1);
	while (end > start && char_check(set, *(s1 + (end - 1))))
		end--;
	trim = str_new(end - start);
	if (!trim)
		return (NULL);
	i = 0;
	while ((start + i) < end)
	{
		*(trim + i) = *(s1 + (start + i));
		i++;
	}
	*(trim + i) = '\0';
	return (trim);
}

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*bb;
	unsigned char	cc;
	size_t			i;

	bb = (unsigned char *) b;
	cc = (unsigned char) c;
	i = 0;
	while (i < len)
	{
		bb[i] = cc;
		i++;
	}
	return (b);
}

int	len_of_number(long long n)
{
	int	len;

	len = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		n *= -1;
		len += 1;
	}
	while (n)
	{
		len += 1;
		n /= 10;
	}
	return (len);
}

static char	*fill(char *ptr, long long ln, int size)
{
	int	i;

	if (ln == 0)
	{
		ptr[0] = '0';
		ptr[1] = 0;
		return (ptr);
	}
	if (ln < 0)
	{
		ptr[0] = '-';
		ln *= -1;
	}
	i = size - 1;
	while (ln)
	{
		ptr[i] = '0' + ln % 10;
		ln /= 10;
		i--;
	}
	ptr[size] = 0;
	return (ptr);
}

char	*ft_itoa(int n)
{
	int			size;
	long long	ln;
	char		*ptr;

	ln = (long long)n;
	size = len_of_number(ln);
	ptr = malloc(size + 1);
	if (ptr == NULL)
		return (NULL);
	fill(ptr, ln, size);
	return (ptr);
}
