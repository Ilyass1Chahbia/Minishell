/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfellahi <sfellahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 10:13:20 by sfellahi          #+#    #+#             */
/*   Updated: 2024/10/09 18:23:32 by sfellahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell1.h"

static void	handle_plus_case(t_env **env_list, char *name, char *value)
{
	t_env	*existing;
	char	*new_value;

	existing = ft_getenv(*env_list, name);
	if (existing && existing->value)
	{
		new_value = ft_strjoin(existing->value, value);
		free(existing->value);
		existing->value = new_value;
		existing->exported = 1;
	}
	else
		update_or_create_env(env_list, name, value, 0);
}

static void	restore_string(char *equal_sign, char *name,
	size_t name_len, int has_plus)
{
	*equal_sign = '=';
	if (has_plus)
		name[name_len - 1] = '+';
}

static void	process_valid_identifier(t_env **env_list, char *name,
		char *value, int has_plus)
{
	if (has_plus)
		handle_plus_case(env_list, name, value);
	else
		update_or_create_env(env_list, name, value, 0);
}

void	handle_equal(t_env **env_list, char *arg, char *equal_sign, int *n)
{
	char	*name;
	char	*value;
	int		has_plus;
	size_t	name_len;

	has_plus = 0;
	*equal_sign = '\0';
	name = arg;
	value = equal_sign + 1;
	name_len = ft_strlen1(name);
	if (name_len > 0 && name[name_len - 1] == '+')
	{
		has_plus = 1;
		name[name_len - 1] = '\0';
	}
	if (is_valid_identifier(name))
		process_valid_identifier(env_list, name, value, has_plus);
	else
	{
		made_printf("minishell: export: `%s': not a valid identifier\n", arg);
		*n = 1;
	}
	restore_string(equal_sign, name, name_len, has_plus);
}

void	ft_export(t_env **env_list, char **args)
{
	int		i;
	char	*equal_sign;
	int		n;

	i = 1;
	n = 0;
	if (!args[i])
	{
		print_sorted_env(*env_list);
		return ;
	}
	while (args[i])
	{
		equal_sign = ft_strchr(args[i], '=');
		if (equal_sign)
			handle_equal(env_list, args[i], equal_sign, &n);
		else
			handle_no_equal(env_list, args[i], &n);
		i++;
	}
	if (n != 1)
		ft_exit_code(0, 1);
	else
		ft_exit_code(1, 1);
}
