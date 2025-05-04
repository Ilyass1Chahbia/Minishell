/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_single_command.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilchahbi <ilchahbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 11:47:59 by sfellahi          #+#    #+#             */
/*   Updated: 2024/10/15 12:05:05 by ilchahbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell1.h"

char	*get_output_file(char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		if (ft_strcmp(args[i], ">") == 0 && args[i + 1])
			return (ft_strdup1(args[i + 1]));
		i++;
	}
	return (NULL);
}

static int	handle_input_redirection(t_env **env_list, t_commandd_info *info)
{
	if (env_list && *env_list)
	{
		(*env_list)->input_error_check = handle_redirections11(info->args,
				&info->fd_in, &info->fd_out);
		if ((*env_list)->input_error_check)
		{
			ft_putstr_fd("", 2);
			return (1);
		}
	}
	return (0);
}

static void	handle_output_redirection11(t_commandd_info *info)
{
	char	*output_file;

	if (info->fd_out == -1)
	{
		output_file = get_output_file(info->args);
		if (output_file)
		{
			info->fd_out = open(output_file,
					O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (info->fd_out == -1)
			{
				perror("Minishell: Error opening output file");
				free(output_file);
				return ;
			}
			free(output_file);
		}
	}
}

void	execute_single_command(char *cmd, t_env **env_list)
{
	t_commandd_info	info;

	ft_memset(&info, 0, sizeof(t_commandd_info));
	info.fd_in = -1;
	info.fd_out = -1;
	info.original_stdin = -1;
	info.original_stdout = -1;
	initialize_command_info(&info, cmd);
	setup_io(env_list, &info);
	if (handle_input_redirection(env_list, &info))
	{
		cleanup_and_exit(&info);
		return ;
	}
	handle_output_redirection11(&info);
	handle_command(&info, env_list);
	cleanup_and_exit(&info);
}
