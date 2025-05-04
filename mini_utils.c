/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilchahbi <ilchahbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 11:39:20 by ilchahbi          #+#    #+#             */
/*   Updated: 2024/10/13 10:05:14 by ilchahbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fill_xp(t_tower *tower)
{
	t_info	*node;

	node = tower->top;
	while (node)
	{
		if ((ft_strcmp(node->data, "export") == 0) && (node->next != NULL
				&& node->next->type == SPC) && (node->next->next != NULL
				&& node->next->next->type == DLR))
		{
			node->next->next->data
				= ft_strdup(change_spc(node->next->next->data));
		}
		node = node->next;
	}
}

void	special_cases(t_tower *tower)
{
	t_info	*node;

	node = tower->top;
	while (node)
	{
		if (node->type == DQT && node->data[0] == '\"' && node->data[1] == '\"')
		{
			node->data = ft_strdup("\"\x05\"");
		}
		node = node->next;
	}
}

void	skip_while(t_tower *tower)
{
	t_info	*node;

	node = tower->top;
	while (node)
	{
		skip_dqt(&node);
		node = node->next;
	}
}

void	fix_space_pipe(t_info **node)
{
	t_info	*head;

	head = *node;
	while (*node)
	{
		if ((*node)->type == SPC)
		{
			(*node)->data = ft_strdup("\a");
		}
		else if ((*node)->type == PIPE)
		{
			(*node)->data = ft_strdup("\e");
			ft_exit_code(0, 1);
		}
		(*node) = (*node)->next;
	}
	*node = head;
}

void	space_tab(t_tower *tower)
{
	t_info	*node;

	node = tower->top;
	fix_space_pipe(&node);
}
