/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfellahi <sfellahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 12:57:17 by sfellahi          #+#    #+#             */
/*   Updated: 2024/10/15 23:55:41 by sfellahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell1.h"

char	*expand_user(char *arg, char *user)
{
	static char	expanded_path[PATH_MAX];

	if (!user)
	{
		made_printf("cd: USER not set\n");
		return (NULL);
	}
	ft_strcpy(expanded_path, "/Users/");
	ft_strcat(expanded_path, arg + 1);
	return (expanded_path);
}

char	*expand_tilde(char *arg, t_env *env_list)
{
	char	*home;
	char	*user;

	if (arg[1] == '\0' || arg[1] == '/')
	{
		home = get_env_value(env_list, "HOME");
		if (!home)
		{
			made_printf("minishell: cd: HOME not set\n");
			ft_exit_code(1, 1);
			return (NULL);
		}
		return (expand_home(arg, home));
	}
	user = get_env_value(env_list, "USER");
	if (!user)
	{
		made_printf("minishell: cd: USER not set\n");
		return (NULL);
	}
	return (expand_user(arg, user));
}

char	*get_target_dir(char **args, t_env *env_list)
{
	char	*home;

	if (!args[1] || (args[1][0] == '~' && args[1][1] == '\0'))
	{
		home = get_env_value(env_list, "HOME");
		if (!home)
		{
			made_printf("minishell: cd: HOME not set\n");
			ft_exit_code(1, 1);
			return (NULL);
		}
		return (home);
	}
	if (args[1][0] == '~')
		return (expand_tilde(args[1], env_list));
	return (args[1]);
}

void	update_pwd(t_env **env_list)
{
	char	*old_pwd;
	char	new_pwd[PATH_MAX];

	old_pwd = get_env_value(*env_list, "PWD");
	if (old_pwd && getcwd(new_pwd, sizeof(new_pwd)) != NULL)
	{
		update_env(env_list, "OLDPWD", old_pwd);
		update_env(env_list, "PWD", new_pwd);
	}
}

void	ft_cd(char **args, t_env **env_list)
{
	char	*target_dir;
	char	p[PATH_MAX];
	int		k;

	k = 0;
	target_dir = get_target_dir(args, *env_list);
	if (!target_dir)
		return ;
	getcwd(p, sizeof(p));
	if (chdir(target_dir) != 0)
	{
		made_printf("minishell: cd: %s: %s\n", target_dir, strerror(errno));
		ft_exit_code(1, 1);
		return ;
	}
	if (getcwd(p, sizeof(p)) == NULL)
	{
		ft_putstr_fd("cd: No such file or directory\n", 2);
		ft_exit_code(1, 1);
		k = 1;
	}
	update_pwd(env_list);
	if (k != 1)
		ft_exit_code(0, 1);
}
