/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_tools.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfellahi <sfellahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 13:13:05 by sfellahi          #+#    #+#             */
/*   Updated: 2024/10/09 10:30:05 by sfellahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell1.h"

int	update_existing_env(t_env *env_list, const char *key, const char *value)
{
	t_env	*current;

	current = env_list;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			free(current->value);
			current->value = ft_strdup1(value);
			return (1);
		}
		current = current->next;
	}
	return (0);
}

void	add_new_env(t_env **env_list, const char *key, const char *value)
{
	t_env	*new_node;

	new_node = (t_env *)malloc(sizeof(t_env));
	if (new_node)
	{
		new_node->key = ft_strdup1(key);
		new_node->value = ft_strdup1(value);
		if (!new_node->key || !new_node->value)
		{
			free(new_node->key);
			free(new_node->value);
			free(new_node);
			return ;
		}
		new_node->next = NULL;
		new_node->exported = 1;
		ft_lstadd_back(env_list, new_node);
	}
}

void	update_env(t_env **env_list, const char *key, const char *value)
{
	if (*env_list && !update_existing_env(*env_list, key, value))
	{
		add_new_env(env_list, key, value);
	}
}

void	handle_child_process(char **args, char **cmnd, t_env **env_list)
{
	signal(SIGQUIT, SIG_DFL);
	child_process(args, cmnd, env_list);
}
