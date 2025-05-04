/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_tools1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfellahi <sfellahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 10:41:01 by sfellahi          #+#    #+#             */
/*   Updated: 2024/10/09 12:17:12 by sfellahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell1.h"

void	free_env_array_partial(char **env_array, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		free(env_array[i]);
		i++;
	}
	free(env_array);
}

void	handle_plus_equal(t_env **env_list, char *arg, char *plus_equal)
{
	char	*name;
	char	*value;

	*plus_equal = '\0';
	name = arg;
	value = plus_equal + 2;
	if (is_valid_identifier(name))
		update_or_create_env(env_list, name, value, 1);
	else
	{
		made_printf("minishell: export: `%s': not a valid identifier\n", arg);
		ft_exit_code(1, 1);
	}
	*plus_equal = '+';
}

void	print_sorted_env(t_env *env_list)
{
	int		count;
	char	**env_array;
	int		i;

	count = count_exported_env(env_list);
	if (count == 0)
		return ;
	env_array = malloc(sizeof(char *) * (count + 1));
	if (!env_array)
		return ;
	i = populate_env_array(env_list, env_array);
	env_array[i] = NULL;
	ft_sort_string_arr(env_array);
	print_env_array(env_list, env_array);
	free_env_array(env_array);
}

int	populate_env_array(t_env *env_list, char **env_array)
{
	int		i;
	t_env	*current;

	i = 0;
	current = env_list;
	while (current)
	{
		if (current->exported)
		{
			env_array[i] = ft_strdup1(current->key);
			if (!env_array[i])
			{
				free_env_array_partial(env_array, i);
				return (-1);
			}
			i++;
		}
		current = current->next;
	}
	return (i);
}

void	print_env_array(t_env *env_list, char **env_array)
{
	int		i;
	t_env	*env;

	i = 0;
	while (env_array[i])
	{
		env = ft_getenv(env_list, env_array[i]);
		if (env->value == NULL)
			made_printf("declare -x %s\n", env->key);
		else
			made_printf("declare -x %s=\"%s\"\n", env->key, env->value);
		i++;
	}
}
