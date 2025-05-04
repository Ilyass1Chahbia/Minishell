/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilchahbi <ilchahbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 12:41:39 by ilchahbi          #+#    #+#             */
/*   Updated: 2024/09/08 12:42:55 by ilchahbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	under_cover(t_info	*node)
{
	int		n;

	n = 0;
	while (node->data[n])
	{
		node->data[n] *= -1;
		n++;
	}
}

void	qts_check(t_info *node)
{
	int	n;

	n = 0;
	ft_switchup(node->data);
	while (node->data[n])
	{
		if (!ft_isascii(node->data[n]))
		{
			ft_switchup(node->data);
		}
		n++;
	}
}

t_info	*qts_delim(t_info *node)
{
	while (node)
	{
		if (node->type == QT || node->type == DQT)
			return (node);
		node = node->next;
	}
	return (NULL);
}

int	valid_nodes(t_info *node)
{
	if (node->type == QT || node->type == DQT || node->type == DLR)
		return (1);
	else
		return (0);
}
