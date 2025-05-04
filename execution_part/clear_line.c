/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilchahbi <ilchahbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 10:25:31 by ilchahbi          #+#    #+#             */
/*   Updated: 2024/10/14 12:28:08 by ilchahbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell1.h"

int	count_chars(const char *str, int c)
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
			if (str[i] == c)
				break ;
			i++;
		}
		else if (c == 32)
		{
			if (!ft_isspace(str[i]))
				len++;
			if (ft_isspace(str[i]))
				break ;
			i++;
		}
	}
	return (len);
}

char	*create_string_without_whitespace(const char *str)
{
	char	*new_str;
	int		len;
	int		i;
	int		j;

	len = count_chars(str, 32);
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
		if (ft_isspace(str[i]))
			break ;
		i++;
	}
	new_str[j] = '\0';
	return (new_str);
}

char	*create_string_without_char(const char *str, int c)
{
	char	*new_str;
	int		len;
	int		i;
	int		j;

	len = count_chars(str, c);
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
		if (str[i] == c)
			break ;
		i++;
	}
	new_str[j] = '\0';
	return (new_str);
}

char	*create_string_without_bell(const char *str, int c)
{
	if (c == 32)
		return (create_string_without_whitespace(str));
	else
		return (create_string_without_char(str, c));
}

char	**remove_any_character(char **str, int c)
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
		res[i] = create_string_without_bell(str[i], c);
		if (!res[i])
			return (ft_failsafe(res, i), NULL);
		i++;
	}
	res[i] = NULL;
	return (res);
}
