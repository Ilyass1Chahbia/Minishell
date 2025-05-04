/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilchahbi <ilchahbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 14:19:28 by ilchahbi          #+#    #+#             */
/*   Updated: 2024/09/28 12:00:51 by ilchahbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	its_red_2(t_info *node)
{
	if (!node)
		return (0);
	if (node->type == REDIN || node->type == REDOUT
		|| node->type == APPND || node->type == HERDOC)
		return (1);
	else
		return (0);
}

int	red_check_2(t_info *node)
{
	if (its_red_2(node->next) || (its_red_2(node) && node->next == NULL)
		|| (node->next->type == SPC && node->next->next == NULL)
		|| (node->next->type == SPC && its_red_2(node->next->next))
		|| (node->next->type == SPC && node->next->next->type == PIPE))
		return (0);
	return (1);
}

int	handle_syntax_2(t_tower *tower, t_info *src)
{
	t_info	*tempo;

	tempo = tower->top;
	while (tempo)
	{
		if (tempo->type == PIPE)
		{
			if (!pipe_check(tempo))
				return (0);
		}
		else if (its_red_2(tempo))
		{
			if (!red_check_2(tempo))
				return (0);
		}
		else if (tempo->type == ARG)
		{
			if (!check_arg(tempo))
				return (0);
		}
		if (tempo == src)
			break ;
		tempo = tempo->next;
	}
	return (1);
}

int	herdoc_syntax(t_info *node)
{
	if (node->type == HERDOC && (node->next == NULL
			|| (node->next->type == SPC && node->next->next == NULL)
			|| its_red(node->next) || node->next->type == HERDOC
			|| (node->next->type == SPC && (its_red(node->next->next)
					|| node->next->next->type == HERDOC))))
		return (0);
	if (node->type == HERDOC && (node->next == NULL
			|| (node->next->type == SPC && node->next->next == NULL)
			|| (node->next->type == SPACE && node->next->next->type == PIPE)
			|| node->next->type == PIPE))
	{
		return (0);
	}
	return (1);
}

int	count_heredoc(t_info *node)
{
	int	n;

	n = 0;
	while (node)
	{
		if (node->type == HERDOC && ((node->next != NULL
					&& (node->next->type == ARG || node->next->type == DQT
						|| node->next->type == QT || node->next->type == DLR))
				|| (node->next != NULL && node->next ->type == SPC
					&& node->next->next != NULL
					&& (node->next->next->type == ARG
						|| node->next->next->type == DQT
						|| node->next->next->type == QT
						|| node->next->next->type == DLR))))
			n++;
		node = node->next;
	}
	return (n);
}
