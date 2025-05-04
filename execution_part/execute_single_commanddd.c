/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_single_commanddd.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilchahbi <ilchahbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 12:22:14 by sfellahi          #+#    #+#             */
/*   Updated: 2024/10/14 14:29:19 by ilchahbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell1.h"

void	setup_redirections(int fd_in, int fd_out, t_env **env_list)
{
	if (fd_in != -1)
	{
		dup2(fd_in, STDIN_FILENO);
		close(fd_in);
	}
	else if (ft_cal_here_doc((*env_list)->pipeeee[0]) > 0)
	{
		dup2((*env_list)->pipeeee[0]
		[ft_cal_here_doc((*env_list)->pipeeee[0]) - 1],
			STDIN_FILENO);
		close(*(*env_list)->pipeeee[0]);
	}
	if (fd_out != -1)
	{
		dup2(fd_out, STDOUT_FILENO);
		close(fd_out);
	}
	if ((*env_list)->fd_pipe1[0] != -1)
	{
		dup2((*env_list)->fd_pipe1[0], STDIN_FILENO);
		close((*env_list)->fd_pipe1[0]);
	}
}

void	initialize_command_info(t_commandd_info *info, char *cmd)
{
	info->args = ft_split(cmd, '\a');
	info->cmnd = ft_split_spaces(cmd);
	info->fd_out = -1;
	info->fd_in = -1;
	info->return_value = 0;
}
