/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_single_commandd.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilchahbi <ilchahbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 11:54:09 by sfellahi          #+#    #+#             */
/*   Updated: 2024/10/11 18:15:43 by ilchahbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell1.h"

void	handle_parent_process(pid_t pid, int *return_ss)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
		{
			write(STDOUT_FILENO, "\n", 1);
			g_sg = 0;
		}
		else if (WTERMSIG(status) == SIGQUIT)
			write(STDOUT_FILENO, "Quit: 3\n", 8);
		*return_ss = WTERMSIG(status) + 128;
	}
	else
		*return_ss = WEXITSTATUS(status);
}

void	execute_external_command(char **args, char **cmnd,
		t_env **env_list, int *return_ss)
{
	pid_t	pid;

	signal(SIGINT, ft_signals_child);
	pid = fork();
	if (pid == 0)
		handle_child_process(args, cmnd, env_list);
	else if (pid > 0)
		handle_parent_process(pid, return_ss);
	else
		perror("fork");
	ft_exit_code(*return_ss, 1);
	signal_func();
}

void	cleanup_restore_stdin(t_commandd_info *info, int stdin_fd, int in_fd)
{
	(void)info;
	if (stdin_fd != -1)
	{
		dup2(stdin_fd, STDIN_FILENO);
		close(stdin_fd);
	}
	if (in_fd != -1)
		close(in_fd);
}

void	cleanup_restore_stdout(t_commandd_info *info, int stdout_fd, int out_fd)
{
	(void)info;
	if (stdout_fd != -1)
	{
		dup2(stdout_fd, STDOUT_FILENO);
		close(stdout_fd);
	}
	if (out_fd != -1)
		close(out_fd);
}

void	cleanup_and_restore(t_commandd_info *info)
{
	int	stdin_fd;
	int	stdout_fd;
	int	in_fd;
	int	out_fd;

	stdin_fd = info->original_stdin;
	stdout_fd = info->original_stdout;
	in_fd = info->fd_in;
	out_fd = info->fd_out;
	info->original_stdin = -1;
	info->original_stdout = -1;
	info->fd_in = -1;
	info->fd_out = -1;
	cleanup_restore_stdin(info, stdin_fd, in_fd);
	cleanup_restore_stdout(info, stdout_fd, out_fd);
	free_string_array2(info->args);
}
