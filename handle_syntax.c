/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_syntax.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilchahbi <ilchahbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 10:08:51 by ilchahbi          #+#    #+#             */
/*   Updated: 2024/09/08 12:37:17 by ilchahbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pipe_check(t_info *node)
{
	if (node->next == NULL || node->previous == NULL || its_red(node->previous)
		|| (node->previous->previous != NULL && node->previous->type == SPC
			&& its_red(node->previous->previous))
		|| (node->previous->type == SPACE && node->previous->previous == NULL)
		|| (node->next->type == SPACE && node->next->next == NULL)
		|| (node->next->type == SPACE && node->next->next->type == PIPE)
		|| node->next->type == PIPE)
		return (0);
	return (1);
}

int	red_check(t_info *node)
{
	if ((node->previous != NULL && node->previous->type == HERDOC))
		return (1);
	if (its_red(node->next) || node->next == NULL
		|| (node->next->type == SPACE && node->next->next == NULL)
		|| (node->next->type == SPACE && its_red(node->next->next))
		|| (node->next->type == SPC && node->next->next != NULL
			&& node->next->next->type == PIPE))
		return (0);
	return (1);
}

int	and_para(char *res)
{
	int	n;

	n = 0;
	while (res[n])
	{
		if (res[n] == '&' || res[n] == '(' || res[n] == ')')
			return (0);
		else
			n++;
	}
	return (1);
}

int	check_arg(t_info *node)
{
	if (!and_para(node->data))
		return (0);
	else
		return (1);
}

int	handle_syntax(t_tower *tower)
{
	t_info	*tempo;

	tempo = tower->top;
	while (tempo)
	{
		if (post_heredoc(tower, tempo))
			return (1);
		if (tempo->type == PIPE)
		{
			if (!pipe_check(tempo))
				return (0);
		}
		else if (its_red(tempo))
		{
			if (!red_check(tempo))
				return (0);
		}
		else if (tempo->type == ARG)
		{
			if (!check_arg(tempo))
				return (0);
		}
		tempo = tempo->next;
	}
	return (1);
}
