/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_cases.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilchahbi <ilchahbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 04:07:04 by ilchahbi          #+#    #+#             */
/*   Updated: 2024/09/08 11:26:25 by ilchahbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	red_tokens(t_tower *res, char *input, int n)
{
	int		old_n;
	t_info	*node;

	node = NULL;
	old_n = n;
	if (input[n] == '>')
	{
		n = reds_case1(res, node, input, n);
	}
	else if (input[n] == '<')
	{
		n = reds_case2(res, node, input, n);
	}
	return (n - old_n);
}

int	others_hand(t_tower *res, char *input, int n)
{
	int	m;

	m = n;
	while (not_like_us(input[m]) && input[m] != '$')
	{
		m++;
	}
	tower_addback(res, alloc_struct(ft_substr1337(input, n, m - n), ARG));
	return (m - n);
}

int	ft_quotes_hand(t_tower *res, char *input, int n, int k)
{
	int	sz;
	int	dz;

	sz = 0;
	dz = 0;
	if (k == 1)
		sz = in_qt(input, n);
	else if (k == 2)
		dz = in_dqt(input, n);
	if (input[n] == '\'')
	{
		tower_addback(res, alloc_struct(ft_substr1337(input, n, sz - n), QT));
		return (sz);
	}
	else if (input[n] == '\"')
	{
		tower_addback(res, alloc_struct(ft_substr1337(input, n, dz - n), DQT));
		return (dz);
	}
	return (1);
}

int	chase_dollars(t_tower *res, char *input, int n)
{
	int	m;

	m = n;
	if (input[n + 1] == 32 || (input[n + 1] >= 9 && input[n + 1] <= 13)
		|| input[n + 1] == '\0' || input[n + 1] == '\n')
	{
		tower_addback(res, alloc_struct(ft_substr1337(input, n, 1), DLR));
		n++;
	}
	else if (input[n + 1] >= '0' && input[n + 1] <= '9')
	{
		tower_addback(res, alloc_struct(ft_substr1337(input, n, 2), DLR));
		n += 2;
	}
	else
	{
		n = dlr_case(input, n);
		tower_addback(res, alloc_struct(ft_substr1337(input, m, n - m), DLR));
	}
	return (n);
}

int	token_cases(t_tower *res, char *input, int n)
{
	if (input[n] == '\0' || !input)
		return (n);
	if (input[n] == '>' || input[n] == '<')
		n += red_tokens(res, input, n);
	if (input[n] == '|')
	{
		tower_addback(res, alloc_struct(ft_substr1337(input, n, 1), PIPE));
		n++;
	}
	if (input[n] == 32 || (input[n] >= 9 && input[n] <= 13))
	{
		while (input[n] == 32 || (input[n] >= 9 && input[n] <= 13))
			n++;
		tower_addback(res, alloc_struct(ft_strdup(" "), SPC));
	}
	if (input[n] == '$')
		n = chase_dollars(res, input, n);
	if (input[n] == '\'')
		n = ft_quotes_hand(res, input, n, 1);
	if (input[n] == '\"')
		n = ft_quotes_hand(res, input, n, 2);
	else
		n += others_hand(res, input, n);
	return (n);
}
