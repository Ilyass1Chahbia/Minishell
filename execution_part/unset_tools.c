/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilchahbi <ilchahbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 17:17:47 by sfellahi          #+#    #+#             */
/*   Updated: 2024/10/06 13:09:15 by ilchahbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell1.h"

int	compare_content(const void *content, const char *var_name)
{
	const char	*env_str;
	size_t		var_name_len;

	env_str = (const char *)content;
	var_name_len = ft_strlen1(var_name);
	if (ft_strncmp(env_str, var_name, var_name_len)
		== 0 && env_str[var_name_len] == '=')
		return (0);
	return (1);
}

void	del_content(void *content)

{
	if (content)
	{
		free(content);
	}
}

int	is_valid_env_name(const char *name)

{
	if (!name || !*name)
		return (0);
	if (!ft_isalpha(*name) && *name != '_')
		return (0);
	while (*++name)
	{
		if (!ft_isalnum(*name) && *name != '_')
			return (0);
	}
	return (1);
}

void	free_split(char **split, size_t count)
{
	size_t	i;

	i = 0;
	while (i < count)
	{
		free(split[i]);
		i++;
	}
	free(split);
}
