/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfellahi <sfellahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 11:20:17 by sfellahi          #+#    #+#             */
/*   Updated: 2024/10/16 13:16:46 by sfellahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell1.h"

void	init_default_env(t_env **env_list)
{
	char	*newpwd;
	char	d[PATH_MAX];

	newpwd = getcwd(d, sizeof(d));
	ft_lstadd_back(env_list,
		ft_lstnew_env(newpwd,
			0));
	ft_lstadd_back(env_list, ft_lstnew_env("_=/usr/bin/env", 0));
	ft_lstadd_back(env_list,
		ft_lstnew_env("PATH=/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin",
			1));
}

void	process_env_variable(t_env **env_list, char *env_var,
		t_env **shlvl_node)
{
	t_env	*new_env;

	new_env = ft_lstnew_env(env_var, 0);
	if (!new_env)
		return ;
	if (new_env)
	{
		if (ft_strcmp(new_env->key, "SHLVL") == 0)
			*shlvl_node = new_env;
		ft_lstadd_back(env_list, new_env);
	}
}

void	update_shlvl(t_env *shlvl_node)
{
	int	current_level;

	current_level = ft_atoi(shlvl_node->value);
	free (shlvl_node->value);
	if (current_level >= 999)
		shlvl_node->value = ft_strdup1("");
	else if (current_level < 0)
		shlvl_node->value = ft_strdup1("0");
	else
	{
		shlvl_node->value = ft_itoa(current_level + 1);
	}
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && (s1[i] || s2[i]))
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

void	handle_no_equal(t_env **env_list, char *arg, int *n)
{
	t_env	*existing;
	t_env	*new_node;

	if (is_valid_identifier(arg))
	{
		existing = ft_getenv(*env_list, arg);
		if (!existing)
		{
			new_node = malloc(sizeof(t_env));
			if (new_node)
			{
				new_node->key = ft_strdup1(arg);
				new_node->value = NULL;
				new_node->exported = 1;
				new_node->next = NULL;
				ft_lstadd_back(env_list, new_node);
			}
		}
		else
			existing->exported = 1;
	}
	else
		return (made_printf("export: `%s': not a valid identifier\n", arg),
			*n = 1, (void)0);
}
