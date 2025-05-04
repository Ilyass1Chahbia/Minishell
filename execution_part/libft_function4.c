/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_function4.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfellahi <sfellahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 15:03:35 by sfellahi          #+#    #+#             */
/*   Updated: 2024/09/28 12:06:50 by sfellahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell1.h"

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*result;

	if (!s1 || !s2)
		return (NULL);
	result = ft_strjoin(s1, s2);
	return (result);
}

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

char	*ft_strndup(const char *s, size_t n)
{
	char	*result;
	size_t	len;
	size_t	i;

	len = 0;
	while (len < n && s[len] != '\0')
		len++;
	result = (char *)malloc(sizeof(char) * (len + 1));
	if (result == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		result[i] = s[i];
		i++;
	}
	result[i] = '\0';
	return (result);
}

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*sad;
	size_t			le;

	sad = (unsigned char *) s;
	le = 0;
	while (le < n)
	{
		sad[le] = 0;
		le++;
	}
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;
	size_t	total_size;

	if (count && size && count > (SIZE_MAX / size))
		return (NULL);
	total_size = count * size;
	ptr = malloc(total_size);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, total_size);
	return (ptr);
}
