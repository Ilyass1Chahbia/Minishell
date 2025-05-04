/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xpand_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilchahbi <ilchahbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 10:12:07 by ilchahbi          #+#    #+#             */
/*   Updated: 2024/09/10 19:18:06 by ilchahbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_dqt_case(t_info *node, int n, int m, int l)
{
	char	*xp;
	char	*old;
	char	*post;
	char	*hold;

	xp = ft_strdup("\0");
	if (!xp)
		return ;
	old = ft_substr1337(node->data, 0, m);
	if (!old)
		return ;
	post = ft_substr1337(node->data, n, l - n);
	if (!post)
		return ;
	hold = ft_strjoin1337(old, xp);
	if (!hold)
		return ;
	hold = ft_strjoin1337(hold, post);
	if (!hold)
		return ;
	node->data = ft_strdup(hold);
	if (!(node->data))
		return ;
}

void	replace_env_red(t_info *node, t_env **ev)
{
	int		t;
	t_env	*tmp;

	t = 0;
	tmp = *ev;
	if (!ev)
		return ;
	if (!tmp)
		return ;
	while (tmp)
	{
		if (tmp->value != NULL)
		{
			if (!ft_strcmp1337(node->data + 1, tmp->key))
			{
				if (!(tmp->value))
					node->data = ft_strdup("\0");
				else
					node->data = ft_strdup(tmp->value);
				t = 1;
			}
		}
		tmp = tmp->next;
	}
	env_case_red(t, node);
}

void	replace_env(t_info *node, t_env **ev, int x)
{
	int		t;
	t_env	*tmp;

	t = 0;
	tmp = *ev;
	if (!ev)
		return ;
	if (!tmp)
		return ;
	while (tmp)
	{
		if (tmp->value != NULL)
		{
			if (!ft_strcmp1337(node->data + 1, tmp->key))
			{
				if (!(tmp->value))
					node->data = ft_strdup("\0");
				else
					node->data = ft_strdup(tmp->value);
				t = 1;
			}
		}
		tmp = tmp->next;
	}
	env_case(t, x, node);
}

void	xp_while2(t_info *node, t_env **env)
{
	int	n;

	n = 0;
	while (node->next->data[n])
	{
		if (node->next->data[n] == '$')
		{
			if (ft_isdigit1337(node->next->data[n + 1]))
				replace_nm_dqt(node->next, n);
			else
			{
				replace_env_dqt(node->next, env, n);
			}
		}
		if (node->next->data[n] != '\0')
			n++;
	}
}

void	xp_while3(t_info *node, t_env **env)
{
	int	n;

	n = 0;
	while (node->next->next->data[n])
	{
		if (node->next->next->data[n] == '$')
		{
			if (ft_isdigit1337(node->next->next->data[n + 1]))
				replace_nm_dqt(node->next->next, n);
			else
			{
				replace_env_dqt(node->next->next, env, n);
			}
		}
		if (node->next->next->data[n] != '\0')
			n++;
	}
}
