/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfellahi <sfellahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 11:48:54 by ilchahbi          #+#    #+#             */
/*   Updated: 2024/10/15 23:47:13 by sfellahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell1.h"

void	initialize_builtins(char **builtins)
{
	builtins[0] = "echo";
	builtins[1] = "cd";
	builtins[2] = "pwd";
	builtins[3] = "export";
	builtins[4] = "unset";
	builtins[5] = "env";
	builtins[6] = "ENV";
	builtins[7] = "exit";
	builtins[8] = NULL;
}

int	check_builtin(char *cmd_name, char **builtins)
{
	int	i;

	i = 0;
	while (builtins[i])
	{
		if (ft_strcmp(cmd_name, builtins[i]) == 0)
		{
			return (1);
		}
		i++;
	}
	return (0);
}

int	check_cmd_split(char *cmd, char **builtins)
{
	char	**cmd_split;
	char	*cmd_name;
	int		result;

	cmd_split = ft_split(cmd, '\a');
	cmd_name = cmd_split[0];
	result = check_builtin(cmd_name, builtins);
	ft_free_split(cmd_split);
	return (result);
}

int	check_cmnd_sp(char *cmd, char **builtins)
{
	char	**cmnd_sp;
	char	*cmnd;
	int		result;

	cmnd_sp = ft_split(cmd, ' ');
	cmnd = cmnd_sp[0];
	result = check_builtin(cmnd, builtins);
	ft_free_split(cmnd_sp);
	return (result);
}

int	is_builtin(char *cmd)
{
	char	*builtins[9];

	if (!cmd)
	{
		return (0);
	}
	initialize_builtins(builtins);
	if (check_cmd_split(cmd, builtins))
	{
		return (1);
	}
	if (check_cmnd_sp(cmd, builtins))
	{
		return (1);
	}
	return (0);
}
