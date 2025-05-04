/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilchahbi <ilchahbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 11:41:20 by ilchahbi          #+#    #+#             */
/*   Updated: 2024/10/04 11:31:05 by ilchahbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_switchback(t_info *node)
{
	if (node == NULL)
		return ;
	while (node != NULL)
	{
		if (node->type == QT || node->type == DQT || node->type == DLR)
		{
			if (node->data != NULL)
				ft_switchup(node->data);
		}
		node = node->next;
	}
}

int	error_1(char *input)
{
	if (!ft_quote_mod(input))
	{
		printf("syntax error\n");
		free(input);
		ft_exit_code(258, 1);
		return (0);
	}
	return (1);
}

char	*join_nodes(t_tower *tower, char *res)
{
	t_info	*node;

	node = tower->top;
	while (node)
	{
		res = ft_strjoin1337(res, node->data);
		node = node->next;
	}
	return (res);
}

void	error_2(t_tower *tower)
{
	mark_sweep(tower, 0, 0);
	printf("Syntax Error\n");
	ft_exit_code(258, 1);
}

int	one_sp(t_tower *tower)
{
	t_info	*node;

	node = tower->top;
	if (node->type == SPC && node->next == NULL)
		return (1);
	return (0);
}
