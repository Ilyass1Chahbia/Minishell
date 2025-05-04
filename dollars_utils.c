/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollars_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilchahbi <ilchahbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 16:56:04 by ilchahbi          #+#    #+#             */
/*   Updated: 2024/09/21 17:38:51 by ilchahbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	process_dollar_sequence(char *data, int start, int length)
{
	int	i;

	if (length % 2 == 0)
	{
		i = start;
		while (i < start + length)
		{
			data[i] = -1 * data[i];
			i++;
		}
	}
}

void	handle_dqt_node(t_info *node)
{
	int	n;
	int	d_c;
	int	start_index;

	n = 0;
	d_c = 0;
	start_index = -1;
	while (node->data[n])
	{
		if (node->data[n] == '$')
		{
			if (start_index == -1)
				start_index = n;
			d_c++;
		}
		else if (d_c > 0)
		{
			process_dollar_sequence(node->data, start_index, d_c);
			d_c = 0;
			start_index = -1;
		}
		n++;
	}
	if (d_c > 0)
		process_dollar_sequence(node->data, start_index, d_c);
}

void	dollar_check(t_tower *tower)
{
	t_info	*node;

	node = tower->top;
	while (node)
	{
		if (node->type == DQT)
		{
			handle_dqt_node(node);
		}
		node = node->next;
	}
}

void	rev_dollars(t_tower *tower)
{
	t_info	*node;
	int		n;

	node = tower->top;
	while (node)
	{
		if (node->type == DQT)
		{
			n = 0;
			while (node->data[n])
			{
				if (node->data[n] < 0)
					node->data[n] *= (-1);
				n++;
			}
		}
		node = node->next;
	}
}
