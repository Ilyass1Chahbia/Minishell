/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilchahbi <ilchahbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 19:59:57 by ilchahbi          #+#    #+#             */
/*   Updated: 2024/09/26 16:48:07 by ilchahbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	hide_dilemeter(t_tower	*tower)
{
	t_info	*node;

	node = tower->top;
	while (node != NULL)
	{
		if (node->type == HERDOC && (node->next == NULL
				|| its_red_2(node->next)))
			return ;
		if (node->type == HERDOC
			&& ((node->next != NULL && node->next->type != SPC)
				|| ((node->next != NULL && node->next->type == SPC)
					&& (node->next->next != NULL
						&& node->next->next->type != SPC))))
		{
			if (node->next->type != SPC && valid_nodes(node->next))
				qts_check(node->next);
			else if (node->next->type == SPC && valid_nodes(node->next->next))
				qts_check(node->next->next);
			if (node->next->type != SPC)
				under_cover(node->next);
			else if (node->next->type == SPC)
				under_cover(node->next->next);
		}
		node = node->next;
	}
}

void	revert_dilemeter(t_tower *tower)
{
	t_info	*node;

	node = tower->top;
	while (node)
	{
		if (node->type == HERDOC && (node->next == NULL
				|| its_red_2(node->next)))
			return ;
		if (node->type == HERDOC
			&& ((node->next != NULL && node->next->type != SPC)
				|| ((node->next != NULL && node->next->type == SPC)
					&& (node->next->next != NULL
						&& node->next->next->type != SPC))))
		{
			if (node->next->type != SPC && valid_nodes(node->next))
				qts_check(node->next);
			else if (node->next->type == SPC && valid_nodes(node->next->next))
				qts_check(node->next->next);
			if (node->next->type != SPC)
				under_cover(node->next);
			else if (node->next->type == SPC)
				under_cover(node->next->next);
		}
		node = node->next;
	}
}
