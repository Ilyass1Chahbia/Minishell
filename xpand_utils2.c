/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xpand_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilchahbi <ilchahbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 12:01:25 by ilchahbi          #+#    #+#             */
/*   Updated: 2024/09/20 19:25:36 by ilchahbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	var_check(t_info *node)
{
	int	n;

	if (!node)
		return (0);
	n = 1;
	if (!(node->data) || *(node->data) == '\0')
		return (0);
	while (node->data[n] != '\0')
	{
		if (!ft_isalnum1337(node->data[n]))
			return (0);
		n++;
	}
	return (1);
}

void	skip_dqt(t_info **nd)
{
	if ((*nd)->type == DQT || (*nd)->type == QT)
	{
		(*nd)->data = ft_substr1337((*nd)->data, 1,
				(ft_strlen((*nd)->data) - 2));
	}
}

void	env_case(int t, int x, t_info *node)
{
	if (t != 1 && x == -1)
	{
		node->data = ft_strdup("\0");
	}
}

void	env_case_red(int t, t_info *node)
{
	if (t != 1)
	{
		node->data = ft_strdup("\x12");
	}
}

void	var_case1(t_info *node, t_env **env)
{
	if (var_check(node->next->next))
	{
		if (ft_isdigit(node->next->next->data[1]))
			replace_nm(node->next->next);
		else
			replace_env_red(node->next->next, env);
	}
}
