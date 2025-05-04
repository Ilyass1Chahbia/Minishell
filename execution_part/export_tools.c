/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfellahi <sfellahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 10:25:33 by sfellahi          #+#    #+#             */
/*   Updated: 2024/10/09 10:57:16 by sfellahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell1.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	int	i;
	int	j;

	if (!haystack || !needle)
		return (NULL);
	if (!*needle)
		return ((char *)haystack);
	i = 0;
	while (haystack[i])
	{
		j = 0;
		while (needle[j] && haystack[i + j] && haystack[i + j] == needle[j])
			j++;
		if (!needle[j])
			return ((char *)&haystack[i]);
		i++;
	}
	return (NULL);
}

int	is_valid_identifier(const char *str)
{
	int	i;

	if (!str || !*str || ft_isdigit(*str))
		return (0);
	i = 0;
	while (str[i])
	{
		if (str[i] == '+' && i > 0 && str[i + 1] == '=')
			return (1);
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

void	ft_sort_string_arr(char **arr)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	while (arr[i + 1] != NULL)
	{
		j = i + 1;
		while (arr[j] != NULL)
		{
			if (ft_strcmp(arr[i], arr[j]) > 0)
			{
				temp = arr[i];
				arr[i] = arr[j];
				arr[j] = temp;
			}
			j++;
		}
		i++;
	}
}

t_env	*ft_getenv(t_env *env_list, const char *name)
{
	while (env_list)
	{
		if (ft_strcmp(env_list->key, name) == 0)
			return (env_list);
		env_list = env_list->next;
	}
	return (NULL);
}

int	count_exported_env(t_env *env_list)
{
	int		count;
	t_env	*current;

	count = 0;
	current = env_list;
	while (current)
	{
		if (current->exported)
			count++;
		current = current->next;
	}
	return (count);
}
