/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfellahi <sfellahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 14:29:57 by sfellahi          #+#    #+#             */
/*   Updated: 2024/10/15 23:28:28 by sfellahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell1.h"

void	setup_io(t_env **env_list, t_commandd_info *info)
{
	info->original_stdin = dup(STDIN_FILENO);
	info->original_stdout = dup(STDOUT_FILENO);
	if (env_list && *env_list)
	{
		(*env_list)->original_stdinput = info->original_stdin;
	}
}

void	handle_command(t_commandd_info *info, t_env **env_list)
{
	if (info->args[0] != NULL && env_list && *env_list
		&& !(*env_list)->input_error_check)
	{
		setup_redirections(info->fd_in, info->fd_out, env_list);
		if (is_builtin(info->args[0]))
			execute_builtin(info->args, env_list, 0);
		else
			execute_external_command(info->args, info->cmnd, env_list,
				&info->return_value);
	}
	else if (is_builtin(info->args[0]))
		execute_builtin(info->args, env_list, 1);
}

void	cleanup_and_exit(t_commandd_info *info)
{
	cleanup_and_restore(info);
	free_string_array(info->cmnd);
}
