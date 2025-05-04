/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_utils4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilchahbi <ilchahbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 09:28:23 by ilchahbi          #+#    #+#             */
/*   Updated: 2024/10/02 10:56:39 by ilchahbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid_sequence(t_info *node)
{
	t_info	*current;
	int		found_heredoc;
	int		found_cat;

	if (!node)
		return (0);
	current = node;
	found_heredoc = 0;
	found_cat = 0;
	while (current && current->type != PIPE)
	{
		if (current->type == HERDOC)
			found_heredoc = 1;
		else if (!ft_strcmp(current->data, "cat"))
			found_cat = 1;
		if (found_heredoc && found_cat)
			return (1);
		current = current->next;
	}
	return (0);
}

void	find_nodes(t_info *node, t_info **heredoc
	, t_info **space, t_info **cat)
{
	t_info	*current;

	*heredoc = NULL;
	current = node;
	*space = NULL;
	*cat = NULL;
	while (current && current->type != PIPE)
	{
		if (current->type == HERDOC && !*heredoc)
			*heredoc = current;
		else if (current->type == SPC && !*space && current->next
			&& !ft_strcmp(current->next->data, "cat"))
			*space = current;
		else if (!ft_strcmp(current->data, "cat"))
		{
			*cat = current;
			break ;
		}
		current = current->next;
	}
}

void	move_nodes(t_tower *tower, t_info *heredoc, t_info *space, t_info *cat)
{
	t_info	*prev_space;
	t_info	*next_cat;
	t_info	*prev_heredoc;

	prev_space = space->previous;
	next_cat = cat->next;
	prev_heredoc = heredoc->previous;
	if (prev_space)
		prev_space->next = next_cat;
	if (next_cat)
		next_cat->previous = prev_space;
	if (prev_heredoc)
		prev_heredoc->next = space;
	else
		tower->top = space;
	space->previous = prev_heredoc;
	space->next = cat;
	cat->previous = space;
	cat->next = heredoc;
	heredoc->previous = cat;
	if (heredoc == tower->top)
		tower->top = space;
}

void	process_valid_sequence(t_tower *tower, t_info **node)
{
	t_info	*heredoc;
	t_info	*space;
	t_info	*cat;

	find_nodes(*node, &heredoc, &space, &cat);
	if (heredoc && space && cat)
	{
		move_nodes(tower, heredoc, space, cat);
		*node = cat->next;
	}
	else
	{
		*node = (*node)->next;
	}
}

void	move_sp(t_tower *tower)
{
	t_info	*node;

	node = tower->top;
	while (node)
	{
		if (is_valid_sequence(node))
			process_valid_sequence(tower, &node);
		else
			node = node->next;
	}
}
