/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   the_xpand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilchahbi <ilchahbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 09:43:58 by ilchahbi          #+#    #+#             */
/*   Updated: 2024/09/10 19:19:19 by ilchahbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	replace_nm_dqt(t_info *node, int n)
{
	char	*pre;
	char	*post;
	char	*hold;
	int		m;
	int		l;

	l = ft_strlen(node->data);
	m = n + 2;
	pre = ft_substr1337(node->data, 0, n);
	if (!pre)
		return ;
	post = ft_substr1337(node->data, m, l - m);
	hold = ft_strjoin1337(pre, post);
	node->data = ft_strdup(hold);
}

void	the_xpand(t_tower *tower, t_env **env)
{
	t_info	*node;

	node = tower->top;
	while (node)
	{
		if (!nt_xp(node))
			return ;
		else if (node->type == DLR)
		{
			if (var_check(node))
			{
				if (node->data[0] == '$' && node->data[1] == '?')
					x_c_xpand(node);
				else if (ft_isdigit1337(node->data[1]))
					replace_nm(node);
				else
					replace_env(node, env, -1);
			}
		}
		else if (node->type == DQT)
			xp_while1(node, env);
		node = node->next;
	}
	echo_tower(tower);
}

void	xpand_part2(t_tower *tower, t_env **env)
{
	t_info	*node;

	node = tower->top;
	while (node)
	{
		if (node->type == APPND || node->type == REDIN || node->type == REDOUT)
		{
			if ((node->next != NULL && node->next->type == SPC)
				&& (node->next->next != NULL && node->next->next->type == DLR))
				var_case1(node, env);
			else if (node->next != NULL && node->next->type == DLR)
				var_case2(node, env);
			else if (node->next != NULL && node->next->type == DQT)
				xp_while2(node, env);
			else if ((node->next != NULL && node->next->type == SPC)
				&& (node->next->next != NULL && node->next->next->type == DQT))
				xp_while3(node, env);
		}
		node = node->next;
	}
}

void	big_expand(t_tower *tower, t_env **env)
{
	the_xpand(tower, env);
	xpand_part2(tower, env);
}
