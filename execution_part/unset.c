/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilchahbi <ilchahbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 03:41:12 by sfellahi          #+#    #+#             */
/*   Updated: 2024/10/09 10:55:55 by ilchahbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell1.h"

int	is_valid_identifier11(const char *str)
{
	if (!str || !*str)
		return (0);
	if (!ft_isalpha(*str) && *str != '_')
		return (0);
	while (*++str)
	{
		if (!ft_isalnum(*str) && *str != '_')
			return (0);
	}
	return (1);
}

void	remove_env_var(t_env **env_list, t_env *prev, t_env *current)
{
	if (prev)
		prev->next = current->next;
	else
		*env_list = current->next;
	free(current->key);
	free(current->value);
	free(current);
}

void	unset_single_var(t_env **env_list, char *arg)
{
	t_env	*current;
	t_env	*prev;

	prev = NULL;
	current = *env_list;
	while (current)
	{
		if (ft_strcmp(current->key, arg) == 0)
		{
			remove_env_var(env_list, prev, current);
			break ;
		}
		prev = current;
		current = current->next;
	}
}

void	ft_unset(t_env **env_list, char **args)
{
	int	i;
	int	n;

	i = 1;
	n = 0;
	while (args[i])
	{
		if (!is_valid_identifier11(args[i]))
		{
			made_printf("unset: `%s': not a valid identifier\n", args[i]);
			ft_exit_code(1, 1);
			n = 1;
		}
		else
			unset_single_var(env_list, args[i]);
		i++;
	}
	if (n != 1)
		ft_exit_code(0, 1);
}

int	is_quote(char c)
{
	return (c == '\'' || c == '\"');
}
