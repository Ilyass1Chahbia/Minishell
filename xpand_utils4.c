/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xpand_utils4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilchahbi <ilchahbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 16:30:09 by ilchahbi          #+#    #+#             */
/*   Updated: 2024/10/15 11:04:15 by ilchahbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	x_c_xpand(t_info *node)
{
	char	*post;
	char	*xp;
	char	*hold;
	int		l;

	l = ft_strlen(node->data);
	post = NULL;
	xp = NULL;
	hold = NULL;
	if (node->data[0] == '$' && node->data[1] == '?' && node->data[2] == '\0')
	{
		node->data = ft_strdup(ft_itoa2(ft_exit_code(0, 0)));
	}
	else if (node->data[0] == '$' && node->data[1] == '?'
		&& node->data[2] != '\0')
	{
		xp = ft_itoa2(ft_exit_code(0, 0));
		post = ft_substr1337(node->data, 2, l - 2);
		hold = ft_strjoin1337(xp, post);
		node->data = ft_strdup(hold);
	}
}

int	nt_xp(t_info *node)
{
	if ((node->type == DLR && node->data[0] == '$' && node->data[1] == '\0')
		&& (node->next == NULL || node->next->type != DQT))
		return (0);
	if ((node->type == APPND || node->type == REDIN || node->type == REDOUT)
		&& ((node->next != NULL && node->next->type == DLR)
			|| (node->next != NULL && node->next->type == SPC
				&& node->next->next != NULL && node->next->next->type == DLR)))
		return (0);
	return (1);
}

void	xp_while1(t_info *node, t_env **env)
{
	int	n;

	n = 0;
	if (!node->data)
		return ;
	while (node->data[n])
	{
		if (node->data[n] == '$')
		{
			if (ft_isdigit1337(node->data[n + 1]))
				replace_nm_dqt(node, n);
			else if (node->data[n + 1] == '?')
				x_c_heredoc(&(node->data), n);
			else
				replace_env_dqt(node, env, n);
		}
		if (node->data[n] != '\0')
			n++;
	}
}

void	var_case2(t_info *node, t_env **env)
{
	if (var_check(node->next))
	{
		if (ft_isdigit(node->next->data[1]))
			replace_nm(node->next);
		else
			replace_env_red(node->next, env);
	}
}
