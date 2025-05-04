/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilchahbi <ilchahbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 08:42:26 by ilchahbi          #+#    #+#             */
/*   Updated: 2024/09/20 14:39:55 by ilchahbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	dollar_while(char *result, int dollar_count, int i, int j)
{
	while (result[i])
	{
		if (result[i] == '$')
		{
			dollar_count++;
			if (dollar_count % 2 != 0)
				i++;
			else
			{
				j = i;
				while (result[j])
				{
					result[j] = result[j + 1];
					j++;
				}
				i--;
			}
		}
		else
			i++;
	}
}

char	*keep_one_dollar(char *str)
{
	int		dollar_count;
	int		i;
	char	*result;
	int		j;

	dollar_count = 0;
	i = 0;
	j = 0;
	result = ft_strdup(str);
	if (!result)
		return (NULL);
	dollar_while(result, dollar_count, i, j);
	return (result);
}

void	hide_dollars(t_info *node)
{
	int	n;

	n = 0;
	while (node->data[n] != '\0' && node->data[n] == '$')
	{
		node->data[n] *= -1;
		if (node->data[n] != '\0')
			n++;
	}
}

void	skip_dollars(t_info *node)
{
	char	*hold;

	hold = keep_one_dollar(node->data);
	node->data = ft_strdup(hold);
}

void	handle_dollars(t_tower *tower)
{
	t_info	*node;

	node = tower->top;
	while (node)
	{
		if (node->type == DLR && !ft_isalnum1337(node->data[1])
			&& (node->next != NULL && (node->next->type != DQT
					&& node->next->type != QT)))
		{
			if (count_dollars(node) % 2 == 0)
				hide_dollars(node);
			else if (count_dollars(node) % 2 != 0)
				skip_dollars(node);
		}
		else if (node->type == DLR && !ft_isalnum1337(node->data[1])
			&& (node->next != NULL && (node->next->type == DQT
					|| node->next->type == QT)))
		{
			if (count_dollars(node) % 2 != 0)
				skip_one_dollar(node);
		}
		node = node->next;
	}
}
