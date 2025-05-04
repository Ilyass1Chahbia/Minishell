/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfellahi <sfellahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 09:45:16 by sfellahi          #+#    #+#             */
/*   Updated: 2024/10/05 13:59:32 by sfellahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell1.h"

static int	init_node_with_eq(t_env *newone, char *content, char *eq_sign)
{
	newone->key = ft_substr(content, 0, eq_sign - content);
	if (!newone->key)
	{
		free(newone);
		return (0);
	}
	newone->value = ft_strdup1(eq_sign + 1);
	if (!newone->value)
	{
		free(newone->key);
		free(newone);
		return (0);
	}
	return (1);
}

static int	init_node_without_eq(t_env *newone, char *content)
{
	newone->key = ft_strdup1(content);
	if (!newone->key)
	{
		free(newone);
		return (0);
	}
	newone->value = NULL;
	return (1);
}

t_env	*ft_lstnew(void *content)
{
	t_env	*newone;
	char	*eq_sign;
	int		success;

	newone = (t_env *)malloc(sizeof(t_env));
	if (!newone)
		return (NULL);
	eq_sign = ft_strchr((char *)content, '=');
	if (eq_sign)
		success = init_node_with_eq(newone, content, eq_sign);
	else
		success = init_node_without_eq(newone, content);
	if (!success)
		return (NULL);
	newone->next = NULL;
	newone->exported = 1;
	return (newone);
}

void	ft_lstclear(t_env **lst, void (*del)(void*))
{
	t_env	*to_free;

	while (*lst)
	{
		to_free = *lst;
		*lst = (*lst)->next;
		ft_lstdelone(to_free, del);
	}
	*lst = NULL;
}

void	ft_lstadd_back(t_env **lst, t_env *new)
{
	t_env	*head;

	if (!*lst)
		*lst = new;
	else
	{
		head = *lst;
		while (head->next)
			head = head->next;
		head->next = new;
	}
}
