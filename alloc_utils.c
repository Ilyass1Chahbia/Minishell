/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilchahbi <ilchahbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 03:34:43 by ilchahbi          #+#    #+#             */
/*   Updated: 2024/10/11 12:37:44 by ilchahbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_info	*alloc_struct(char *data, enum e_types type)
{
	t_info	*node;

	if (data == NULL)
		return (NULL);
	node = mark_sweep(NULL, sizeof(t_info), -1);
	if (!node)
		return (NULL);
	node->data = data;
	node->type = type;
	node->previous = NULL;
	return (node);
}

void	tower_init(t_tower *tower)
{
	tower->top = NULL;
	tower->bottom = NULL;
}

t_grb	*alloc_node(void *data)
{
	t_grb	*node;

	if (data == NULL)
		return (NULL);
	node = malloc(sizeof(t_grb));
	if (!node)
		return (NULL);
	node->load = data;
	node->next = NULL;
	return (node);
}

void	ft_lstadd_back_5(t_grb **lst, t_grb *new)
{
	t_grb	*head;

	if (!*lst)
		*lst = new;
	else
	{
		head = *lst;
		while (head->next)
			head = head->next;
		head->next = new;
	}
}

void	*mark_sweep(t_tower *tower, size_t len, int x)
{
	static t_grb	*hood;
	t_grb			*new;
	t_grb			*prev;
	void			*add;

	(void) tower;
	if (x == -1)
	{
		add = malloc(len);
		if (!add)
			exit(1);
		new = alloc_node(add);
		if (!new)
			return (free(add), exit(1), NULL);
		ft_lstadd_back_5(&hood, new);
		return (add);
	}
	else
	{
		prev = hood;
		free_garbage(hood, prev);
		hood = NULL;
		return (NULL);
	}
	return (NULL);
}
