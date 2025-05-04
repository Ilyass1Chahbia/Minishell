/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xpand_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilchahbi <ilchahbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 14:11:45 by ilchahbi          #+#    #+#             */
/*   Updated: 2024/09/21 16:26:30 by ilchahbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	extract_var_name(t_var *var)
{
	var->xp = ft_substr1337(var->node->data, var->m + 1, var->n - var->m - 1);
}

void	replace_var_value(t_var *var)
{
	var->old = ft_substr1337(var->node->data, 0, var->m);
	var->post = ft_substr1337(var->node->data, var->n, var->l - var->n);
	var->hold = ft_strjoin1337(var->old, var->tmp->value);
	var->hold = ft_strjoin1337(var->hold, var->post);
	var->node->data = ft_strdup(var->hold);
	var->i = 1;
}

void	replace_env_dqt_utils(t_var *var)
{
	if (!var->ev)
		return ;
	var->tmp = *var->ev;
	while (var->tmp)
	{
		if (!ft_strcmp1337(var->xp, var->tmp->key))
		{
			replace_var_value(var);
			return ;
		}
		var->tmp = var->tmp->next;
	}
	if (var->i != 1)
		env_dqt_case(var->node, var->n, var->m, var->l);
}

void	replace_env_dqt(t_info *node, t_env **ev, int n)
{
	t_var	var;

	var.node = node;
	var.ev = ev;
	var.n = n;
	var.m = n;
	var.l = ft_strlen(node->data);
	var.i = 0;
	while (var.node->data[var.n] != 32 && !(var.node->data[var.n] >= 9
			&& var.node->data[var.n] <= 13)
		&& var.node->data[var.n] != '\"' && var.node->data[var.n] != '\''
		&& var.node->data[var.n])
	{
		var.n++;
		if (var.node->data[var.n] == '$')
			break ;
	}
	extract_var_name(&var);
	if (!var.xp)
		return ;
	replace_env_dqt_utils(&var);
}
