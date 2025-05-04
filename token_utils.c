/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilchahbi <ilchahbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 10:17:29 by ilchahbi          #+#    #+#             */
/*   Updated: 2024/09/20 14:35:17 by ilchahbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tower	*token_nodes(char *input)
{
	t_tower	*res;
	int		n;

	if (input == NULL)
		return (NULL);
	res = (t_tower *)mark_sweep(NULL, sizeof(t_tower), -1);
	if (!res)
		return (NULL);
	n = 0;
	tower_init(res);
	while (input[n])
	{
		n = token_cases(res, input, n);
		if (n < 0)
			return (free(input), NULL);
	}
	if (res->bottom)
		res->bottom->next = NULL;
	free(input);
	return (res);
}

int	in_dqt(char *input, int n)
{
	if (input[n] == '\"')
		n++;
	while (input[n] != '\"' && input[n])
	{
		n++;
	}
	if (input[n])
		n++;
	return (n);
}

int	in_qt(char *input, int n)
{
	if (input[n] == '\'')
		n++;
	while (input[n] != '\'' && input[n])
	{
		n++;
	}
	if (input[n])
		n++;
	return (n);
}

int	reds_case1(t_tower *res, t_info *node, char *input, int n)
{
	if (input[n + 1] == '>')
	{
		node = alloc_struct(ft_substr1337(input, n, 2), APPND);
		if (!node)
		{
			mark_sweep(res, 0, 0);
			return (0);
		}
		tower_addback(res, node);
		n += 2;
	}
	else if (input[n] != '\0')
	{
		node = alloc_struct(ft_substr1337(input, n, 1), REDOUT);
		if (!node)
		{
			mark_sweep(res, 0, 0);
			return (0);
		}
		tower_addback(res, node);
		n += 1;
	}
	return (n);
}

int	reds_case2(t_tower *res, t_info *node, char *input, int n)
{
	if (input[n + 1] == '<')
	{
		node = alloc_struct(ft_substr1337(input, n, 2), HERDOC);
		if (!node)
		{
			mark_sweep(res, 0, 0);
			return (0);
		}
		tower_addback(res, node);
		n += 2;
	}
	else
	{
		node = alloc_struct(ft_substr1337(input, n, 1), REDIN);
		if (!node)
		{
			mark_sweep(res, 0, 0);
			return (0);
		}
		tower_addback(res, node);
		n += 1;
	}
	return (n);
}
