/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilchahbi <ilchahbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 03:32:36 by ilchahbi          #+#    #+#             */
/*   Updated: 2024/09/20 14:37:39 by ilchahbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_func(char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
}

int	ft_isalpha1337(int c)
{
	return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c == '_'));
}

void	remove_single_dollar(char *result)
{
	int	i;
	int	j;

	i = 0;
	while (result[i])
	{
		if (result[i] == '$')
		{
			j = i;
			while (result[j])
			{
				result[j] = result[j + 1];
				j++;
			}
			return ;
		}
		else
			i++;
	}
}

char	*skip_in_double(char *str)
{
	char	*result;

	result = ft_strdup(str);
	if (!result)
		return (NULL);
	remove_single_dollar(result);
	return (result);
}

void	skip_one_dollar(t_info *node)
{
	char	*hold;

	hold = skip_in_double(node->data);
	if (count_dollars(node) == 1)
	{
		node->data = ft_strdup("\0");
		return ;
	}
	node->data = ft_strdup(hold);
}
