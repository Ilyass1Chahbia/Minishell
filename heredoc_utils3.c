/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilchahbi <ilchahbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 10:48:40 by ilchahbi          #+#    #+#             */
/*   Updated: 2024/10/01 16:54:46 by ilchahbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	replace_expanded(char **res, char *pre, char *value, char *post)
{
	char	*hold;

	hold = ft_strjoin1337(pre, value);
	hold = ft_strjoin1337(hold, post);
	*res = ft_strdup(hold);
}

void	expand_and_replace(t_expand_data *data)
{
	t_env	*tmp;
	char	*post;
	int		l;

	tmp = *(data->ev);
	l = ft_strlen(*(data->res));
	while (tmp)
	{
		if (!ft_strcmp1337(data->xp, tmp->key))
		{
			post = ft_substr1337(*(data->res), data->n, l);
			if (!post)
				return ;
			replace_expanded(data->res, data->pre, tmp->value, post);
			return ;
		}
		tmp = tmp->next;
	}
	*(data->res) = ft_strdup("\0");
}

void	mini_xpand(char **res, t_env **ev, int n)
{
	char			*pre;
	char			*xp;
	int				m;
	t_expand_data	data;

	m = n;
	pre = get_prefix(*res, n);
	n = skip_to_end(*res, n);
	xp = get_expansion(*res, m, n);
	if (!xp)
		return ;
	data.res = res;
	data.ev = ev;
	data.pre = pre;
	data.xp = xp;
	data.n = n;
	expand_and_replace(&data);
}
