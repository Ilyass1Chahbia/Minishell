/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilchahbi <ilchahbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 13:03:52 by ilchahbi          #+#    #+#             */
/*   Updated: 2024/09/20 13:03:52 by ilchahbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cal_here_doc(int *p)
{
	int	i;

	i = -1;
	while (p[++i] != '\x011')
		;
	return (i);
}

void	ft_here_doc_cpy(int *s1, int *s2, int fd)
{
	int	i;
	int	k;

	i = -1;
	k = 0;
	while (s1[++i] != '\x011')
	{
		s2[k++] = s1[i];
	}
	s2[k++] = fd;
	s2[k] = '\x011';
}

void	ft_save_here_doc(int fd, t_tower *tw, int l)
{
	static int	i;
	int			*tmp;
	int			len;

	if (i == 0)
	{
		i++;
		tw->top->pipeee[l] = mark_sweep(NULL, (sizeof(int) * 2), -1);
		if (!tw->top->pipeee[l])
			return ;
		tw->top->pipeee[l][0] = fd;
		tw->top->pipeee[l][1] = '\x011';
	}
	else
	{
		len = ft_cal_here_doc(tw->top->pipeee[l]);
		tmp = tw->top->pipeee[l];
		tw->top->pipeee[l]
			= mark_sweep(NULL, (sizeof(int) * (len + 1 + 1)), -1);
		if (!tw->top->pipeee[l])
			return ;
		ft_here_doc_cpy(tmp, tw->top->pipeee[l], fd);
	}
}

int	cal_lpipe(t_info *n)
{
	int	count;

	count = 0;
	while (n)
	{
		if (n->type == PIPE)
			count++;
		n = n->next;
	}
	return (count);
}

void	replace_nm_heredoc(char **res, int n)
{
	char	*pre;
	char	*post;
	char	*hold;
	int		m;
	int		l;

	l = ft_strlen(*res);
	m = n + 2;
	pre = ft_substr1337(*res, 0, n);
	post = ft_substr1337(*res, m, l - m);
	hold = ft_strjoin1337(pre, post);
	*res = ft_strdup(hold);
}
