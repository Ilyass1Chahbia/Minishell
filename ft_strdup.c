/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilchahbi <ilchahbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 03:46:29 by ilchahbi          #+#    #+#             */
/*   Updated: 2024/10/01 13:32:37 by ilchahbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strlen(const char *s)
{
	int	n;

	if (!s)
		return (0);
	n = 0;
	while (s[n] != '\0')
	{
		n++;
	}
	return (n);
}

char	*ft_strdup(const char *src)
{
	char	*dup;
	int		i;
	int		l;

	if (!src)
		return (NULL);
	i = 0;
	l = ft_strlen(src);
	dup = mark_sweep(NULL, ((sizeof (char) * l) + 1), -1);
	if (!(dup))
	{
		return (0);
	}
	while (src[i] != '\0')
	{
		dup[i] = src[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

int	not_like_us(char t)
{
	if (t == '<' || t == '>' || t == 32 || (t >= 9 && t <= 13)
		|| t == '\n' || t == '\'' || t == '"' || t == '|'
		|| t == '\0')
		return (0);
	else
		return (1);
}

char	*ft_strjoin1337(char *s1, char const *s2)
{
	char	*join;
	size_t	s1_len;
	size_t	s2_len;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	join = mark_sweep(NULL, (s1_len + s2_len + 1), -1);
	if (!join)
		return (NULL);
	ft_strcpy1337(join, s1);
	ft_strcpy1337((join + s1_len), s2);
	return (join);
}
