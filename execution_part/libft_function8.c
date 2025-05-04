/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_function8.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfellahi <sfellahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 12:39:07 by sfellahi          #+#    #+#             */
/*   Updated: 2024/09/26 17:51:12 by sfellahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell1.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	i;
	unsigned int	s_len;
	char			*substr;

	if (!s)
		return (0);
	s_len = ft_strlen1(s);
	if (s_len <= start || len == 0)
	{
		substr = ft_calloc(1, sizeof(char));
		return (substr);
	}
	if (len > ft_strlen1(s + start))
		len = ft_strlen1(s + start);
	substr = malloc((sizeof(char) * (len + 1)));
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
