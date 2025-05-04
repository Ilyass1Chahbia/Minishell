/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilchahbi <ilchahbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 11:12:48 by ilchahbi          #+#    #+#             */
/*   Updated: 2024/10/16 09:52:04 by ilchahbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	insert_spc_before(t_tower *tower, t_info *node)
{
	t_info	*tmp;

	tmp = alloc_struct("\a", SPC);
	if (node->previous)
	{
		tmp->previous = node->previous;
		node->previous->next = tmp;
	}
	else
	{
		tower->top = tmp;
	}
	tmp->next = node;
	node->previous = tmp;
}

void	insert_spc_after(t_info *node)
{
	t_info	*tmp;

	tmp = alloc_struct("\a", SPC);
	tmp->next = node->next;
	node->next->previous = tmp;
	node->next = tmp;
	tmp->previous = node;
}

void	process_node(t_tower *tower, t_info *node)
{
	if (node->type == REDIN || node->type == REDOUT || node->type == APPND
		|| node->type == PIPE)
	{
		if (node->previous == NULL || node->previous->type != SPC)
		{
			insert_spc_before(tower, node);
		}
		if (node->next && node->next->type != SPC)
		{
			insert_spc_after(node);
		}
	}
}

void	spc_reds(t_tower *tower)
{
	t_info	*node;

	node = tower->top;
	while (node)
	{
		process_node(tower, node);
		node = node->next;
	}
}

char	*while_del(t_info *node)
{
	char	*str;
	char	*bk;
	t_info	*tmp;

	str = NULL;
	tmp = node;
	while (tmp && (tmp->type != SPC && tmp->type != PIPE) && !its_red_2(tmp))
	{
		bk = ft_strdup(tmp->data);
		if (tmp->type == DQT || tmp->type == QT)
			heredoc_qt(&bk);
		str = ft_strjoin1337(str, bk);
		tmp = tmp->next;
	}
	return (str);
}
