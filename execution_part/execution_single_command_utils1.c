/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_single_command_utils1.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilchahbi <ilchahbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 11:17:00 by sfellahi          #+#    #+#             */
/*   Updated: 2024/10/13 16:27:00 by ilchahbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell1.h"

void	handle_error(void)
{
	exit(EXIT_FAILURE);
}

void	print_error(char *cmd, char *message, int exit_code)
{
	ft_putstr_fd("Minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putendl_fd(message, 2);
	ft_exit_code(exit_code, 1);
	exit(exit_code);
}

char	*find_command_path(char **args, char **cmnd, t_env **env_list, int *n)
{
	char	*path;

	path = NULL;
	if (cmnd[0] != NULL && cmnd[1] != NULL)
	{
		path = find_the_right_path(cmnd[0], env_list_to_array(*env_list));
		if (path)
			*n = 1;
	}
	if (*n == 0)
	{
		path = find_the_right_path(args[0], env_list_to_array(*env_list));
	}
	return (path);
}

void	handle_execve_error(char *cmd)
{
	char	*cdd;

	cdd = remove_a_character(cmd);
	if (cdd[0] == '\0')
	{
		print_error(cdd, "command not found :", 127);
	}
	if (errno == EACCES)
	{
		if (is_directory(cdd))
			print_error(cdd, ": Is a directory", 126);
		else
			print_error(cdd, ": Permission denied", 126);
	}
	else if (errno == ENOENT)
		print_error(cdd, ": No such file or directory", 127);
	free(cdd);
}

void	execute_command(char *path, t_pvar *ss,
	t_env **env_list, int n)
{
	if (n == 1)
		execve(path, ss->cmnd, env_list_to_array(*env_list));
	else
		execve(path, ss->args, env_list_to_array(*env_list));
	handle_execve_error(ss->args[0]);
}
