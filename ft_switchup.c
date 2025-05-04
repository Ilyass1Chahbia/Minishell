/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_switchup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilchahbi <ilchahbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 02:09:54 by ilchahbi          #+#    #+#             */
/*   Updated: 2024/10/09 10:46:08 by ilchahbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_switchup(char *s)
{
	int		n;
	char	temp;
	char	*res;

	res = s;
	n = 0;
	while (res[n])
	{
		if (res[n] == '"' || res[n] == '\'')
		{
			temp = res[n];
			n++;
			if (res[n] == '\0')
				break ;
			while (res[n])
			{
				if (res[n] == temp)
					break ;
				res[n] *= -1;
				n++;
			}
		}
		if (res[n])
			n++;
	}
}

void	revert_dollars(t_tower *tower)
{
	t_info	*node;
	int		n;

	node = tower->top;
	while (node)
	{
		n = 0;
		if (node->type == DLR)
		{
			while (node->data[n] != '\0' && node->data[n] < 0)
			{
				node->data[n] *= -1;
				if (node->data[n] != '\0')
					n++;
			}
		}
		node = node->next;
	}
}

int	cmp_check(char *res, char *del)
{
	if (ft_strcmp1337(res, del) == 0)
	{
		return (0);
	}
	else
		return (1);
}
