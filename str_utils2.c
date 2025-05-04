/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilchahbi <ilchahbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 12:46:30 by ilchahbi          #+#    #+#             */
/*   Updated: 2024/10/11 11:01:36 by ilchahbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_switch_qt(char *s)
{
	int		n;
	char	temp;
	char	*res;

	res = s;
	n = 0;
	while (res[n])
	{
		if (res[n] == '\'')
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

void	ft_switch_dqt(char *s)
{
	int		n;
	char	temp;
	char	*res;

	res = s;
	n = 0;
	while (res[n])
	{
		if (res[n] == '\"')
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

int	count_dollars(t_info *node)
{
	int	n;
	int	i;

	n = 0;
	if (node == NULL)
		return (0);
	if (node->type == DLR)
	{
		i = 0;
		while (node->data[i] == '$' && node->data[i] != '\0')
		{
			n++;
			i++;
		}
	}
	return (n);
}

int	skip_qt(char *input, int n)
{
	int	f;

	f = 0;
	if (input[n] == '\'' || input[n] == '\"')
		n++;
	while (input[n] != '\'' && input[n] != '\"' && input[n])
	{
		n++;
		f = 1;
	}
	if (input[n] == '\'' || input[n] == '\"')
		f = 0;
	if (f != 0)
		return (INT_MIN);
	if (input[n] == '\'' || input[n] == '\"')
		n++;
	return (n);
}

void	init_fd_heredoc(t_tower *tower)
{
	t_info	*node;
	int		i;

	node = tower->top;
	i = 0;
	node->fd_pipee = mark_sweep(NULL,
			(sizeof(int) * (cal_lpipe(tower->top) + 1)), -1);
	if (!(node->fd_pipee))
		return ;
	while (i <= cal_lpipe(tower->top))
	{
		node->fd_pipee[i] = -1;
		i++;
	}
}
