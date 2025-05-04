/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfellahi <sfellahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 14:07:25 by sfellahi          #+#    #+#             */
/*   Updated: 2024/09/26 17:52:06 by sfellahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell1.h"

void	ft_del(void *data)
{
	free(data);
}

void	ft_lstdelone(t_env *lst, void (*del)(void *))
{
	if (lst != NULL && del != NULL)
	{
		if (lst->key != NULL)
		{
			del(lst->key);
		}
		if (lst->value != NULL)
		{
			del(lst->value);
		}
		free(lst);
	}
}

int	ft_lstsize(t_env *lst)
{
	int	size;

	size = 0;
	while (lst)
	{
		size++;
		lst = lst->next;
	}
	return (size);
}
