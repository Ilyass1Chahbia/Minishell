/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilchahbi <ilchahbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 04:17:15 by ilchahbi          #+#    #+#             */
/*   Updated: 2024/10/05 11:12:50 by ilchahbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	tower_addback(t_tower *tower, t_info *node)
{
	t_tower	*tmp;

	if (node == NULL || tower == NULL)
		return ;
	tmp = tower;
	if (tower->top == NULL)
		tower->top = node;
	else
	{
		tower->bottom->next = node;
		node->previous = tower->bottom;
	}
	tower->bottom = node;
	tower = tmp;
}

int	post_heredoc(t_tower *tower, t_info *src)
{
	t_info	*node;

	node = tower->top;
	while (node)
	{
		if (node == src)
			return (0);
		if (node->type == HERDOC)
			return (1);
		node = node->next;
	}
	return (0);
}

int	custom_strchr(const char *s)
{
	int		n;

	n = 0;
	while (s[n])
	{
		if (s[n] == 32 || (s[n] >= 9 && s[n] <= 13))
			return (1);
		n++;
	}
	if (!ft_isprint(s[0]) && s[1] == '\0')
		return (1);
	return (0);
}

void	ambigious_warn(t_tower *tower)
{
	t_info	*node;

	node = tower->top;
	while (node)
	{
		if (its_red(node))
		{
			if (node->next != NULL && node->next->type == DLR)
			{
				if (custom_strchr(node->next->data))
					node->next->data = ft_strdup("\x12");
			}
			else if ((node->next != NULL && node->next->type == SPC)
				&& (node->next->next != NULL && node->next->next->type == DLR))
			{
				if (custom_strchr(node->next->next->data))
					node->next->next->data = ft_strdup("\x12");
			}
		}
		node = node->next;
	}
}

char	*change_spc(char *str)
{
	char	*result;
	int		i;

	i = 0;
	if (str == NULL)
		return (NULL);
	result = ft_strdup(str);
	if (result == NULL)
		return (NULL);
	while (result[i])
	{
		if (result[i] == ' ')
			result[i] = '\a';
		i++;
	}
	return (result);
}
