/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_line2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilchahbi <ilchahbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 17:39:36 by ilchahbi          #+#    #+#             */
/*   Updated: 2024/10/14 12:42:35 by ilchahbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell1.h"

int	count_chars2(const char *str, int c)
{
	int	len;
	int	i;

	len = 0;
	i = 0;
	while (str[i])
	{
		if (c != 32)
		{
			if (str[i] != c)
				len++;
			i++;
		}
		else if (c == 32)
		{
			if (!ft_isspace(str[i]))
				len++;
			i++;
		}
	}
	return (len);
}

char	*create_string_without_whitespace2(const char *str)
{
	char	*new_str;
	int		len;
	int		i;
	int		j;

	len = count_chars2(str, 32);
	i = 0;
	new_str = (char *)malloc(sizeof(char) * (len + 1));
	if (!new_str)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (!isspace(str[i]))
		{
			new_str[j] = str[i];
			j++;
		}
		i++;
	}
	new_str[j] = '\0';
	return (new_str);
}

char	*create_string_without_char2(const char *str, int c)
{
	char	*new_str;
	int		len;
	int		i;
	int		j;

	len = count_chars2(str, c);
	i = 0;
	new_str = (char *)malloc(sizeof(char) * (len + 1));
	if (!new_str)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] != c)
		{
			new_str[j] = str[i];
			j++;
		}
		i++;
	}
	new_str[j] = '\0';
	return (new_str);
}

char	*create_string_without_bell2(const char *str, int c)
{
	if (c == 32)
		return (create_string_without_whitespace2(str));
	else
		return (create_string_without_char2(str, c));
}

char	**remove_any_character2(char **str, int c)
{
	char	**res;
	int		str_count;
	int		i;

	if (!str)
		return (NULL);
	str_count = 0;
	while (str[str_count])
		str_count++;
	res = (char **)malloc(sizeof(char *) * (str_count + 1));
	if (!res)
		return (NULL);
	i = 0;
	while (str[i])
	{
		res[i] = create_string_without_bell2(str[i], c);
		if (!res[i])
			return (ft_failsafe(res, i), NULL);
		i++;
	}
	res[i] = NULL;
	return (res);
}
