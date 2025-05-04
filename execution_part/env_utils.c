/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilchahbi <ilchahbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 12:17:40 by ilchahbi          #+#    #+#             */
/*   Updated: 2024/10/06 12:22:24 by ilchahbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell1.h"

t_env	*handle_with_eq_sign(t_env *new_node, char *env_str, char *eq_sign)
{
	new_node->key = ft_substr(env_str, 0, eq_sign - env_str);
	new_node->value = ft_strdup1(eq_sign + 1);
	if (!new_node->key || !new_node->value)
	{
		free(new_node->key);
		free(new_node->value);
		free(new_node);
		return (NULL);
	}
	return (new_node);
}

t_env	*handle_without_eq_sign(t_env *new_node, char *env_str)
{
	new_node->key = ft_strdup1(env_str);
	new_node->value = NULL;
	if (!new_node->key)
	{
		free(new_node);
		return (NULL);
	}
	return (new_node);
}

t_env	*process_env_str(t_env *new_node, char *env_str)
{
	char	*eq_sign;

	eq_sign = ft_strchr(env_str, '=');
	if (eq_sign)
	{
		return (handle_with_eq_sign(new_node, env_str, eq_sign));
	}
	else
	{
		return (handle_without_eq_sign(new_node, env_str));
	}
}

t_env	*ft_lstnew_env(char *env_str, int hidden)
{
	t_env	*new_node;

	new_node = (t_env *)malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	new_node->next = NULL;
	new_node->exported = 1;
	new_node->hidden = hidden;
	return (process_env_str(new_node, env_str));
}
