/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfellahi <sfellahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 11:04:45 by sfellahi          #+#    #+#             */
/*   Updated: 2024/10/15 23:38:36 by sfellahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell1.h"

void	ensure_path_exists(t_env **env_list)
{
	if (!get_env_value(*env_list, "PATH"))
		ft_lstadd_back(env_list,
			ft_lstnew_env("PATH=/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin",
				1));
}

void	init_env(t_env **env_list, char **envp)
{
	int		i;
	t_env	*shlvl_node;

	shlvl_node = NULL;
	if (!envp || !envp[0])
		init_default_env(env_list);
	else
	{
		i = 0;
		while (envp[i])
		{
			process_env_variable(env_list, envp[i], &shlvl_node);
			i++;
		}
	}
	if (shlvl_node)
		update_shlvl(shlvl_node);
	else
		ft_lstadd_back(env_list, ft_lstnew_env("SHLVL=1", 0));
	ensure_path_exists(env_list);
}

void	print_env(t_env *env_list)
{
	while (env_list)
	{
		if (env_list->value)
			made_printf("%s=%s\n", env_list->key, env_list->value);
		env_list = env_list->next;
	}
	ft_exit_code(0, 1);
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	const char	*s;
	size_t		i;
	char		*d;

	d = (char *)dest;
	s = (const char *)src;
	i = 0;
	if (dest > src)
	{
		while (n > 0)
		{
			n--;
			d[n] = s[n];
		}
	}
	else if (dest < src)
	{
		i = 0;
		while (i < n)
		{
			d[i] = s[i];
			i++;
		}
	}
	return (dest);
}

void	update_or_create_env(t_env **env_list, char *name, char *value,
		int append)
{
	t_env	*existing;
	char	*trimmed_value;
	char	*new_value;

	existing = ft_getenv(*env_list, name);
	trimmed_value = ft_strtrim(value, "\"");
	if (existing)
	{
		if (append)
		{
			if (existing->value)
				new_value = ft_strjoin(existing->value, trimmed_value);
			else
				new_value = ft_strdup1(trimmed_value);
		}
		else
			new_value = ft_strdup1(trimmed_value);
		free(existing->value);
		existing->value = new_value;
		existing->exported = 1;
	}
	else
		create_new_env(env_list, name, trimmed_value);
	free(trimmed_value);
}
