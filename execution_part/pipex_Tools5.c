/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_Tools5.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilchahbi <ilchahbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 11:41:56 by sfellahi          #+#    #+#             */
/*   Updated: 2024/10/14 14:29:37 by ilchahbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell1.h"

void	close_other_pipes(int pipes[][2], int i, int cmd_count)
{
	int	j;

	j = 0;
	while (j < cmd_count - 1)
	{
		if (j != i - 1 && j != i)
		{
			close(pipes[j][0]);
			close(pipes[j][1]);
		}
		j++;
	}
}

static void	handle_dup2_error(void)
{
	perror("dup2");
	exit(1);
}

void	handle_file_descriptors(int fd_in, int fd_out, t_env **env_list, int i)
{
	(void)env_list;
	if (fd_in != -1)
	{
		if (dup2(fd_in, STDIN_FILENO) == -1)
			handle_dup2_error();
		close(fd_in);
	}
	if (fd_out != -1)
	{
		if (dup2(fd_out, STDOUT_FILENO) == -1)
			handle_dup2_error();
		close(fd_out);
	}
	if ((*env_list)->fd_pipe1[i] != -1)
	{
		if (dup2((*env_list)->fd_pipe1[i], STDIN_FILENO) == -1)
			handle_dup2_error();
	}
}

void	execute_child_process(char *command, t_env **env_list, int pipe_index,
		int cmd_count)
{
	char	**args;
	char	**cmnd;
	int		fd_out;
	int		fd_in;
	int		input_error;

	(void)cmd_count;
	(void)pipe_index;
	fd_out = -1;
	fd_in = -1;
	args = ft_split(command, '\a');
	if (!args)
		exit(1);
	cmnd = ft_split_spaces(command);
	if (!cmnd)
		exit(1);
	input_error = handle_redirections(args, &fd_out, &fd_in);
	if (input_error)
		return (ft_free_array(args), exit(1), (void)0);
	handle_file_descriptors(fd_in, fd_out, env_list, pipe_index);
	execute_command1(args, cmnd, env_list);
	ft_free_array(args);
	ft_free_array(cmnd);
	exit(EXIT_FAILURE);
}

void	wait_for_children(pid_t *pids, int cmd_count, int *last_status)
{
	int	i;
	int	status;

	i = 0;
	while (i < cmd_count)
	{
		waitpid(pids[i], &status, 0);
		if (WIFSIGNALED(status))
		{
			if (WTERMSIG(status) == SIGINT)
			{
				write(STDOUT_FILENO, "\n", 1);
				g_sg = 0;
			}
			else if (WTERMSIG(status) == SIGQUIT)
				write(STDOUT_FILENO, "Quit: 3\n", 8);
			*last_status = WTERMSIG(status) + 128;
		}
		else
			*last_status = WEXITSTATUS(status);
		i++;
	}
	signal_func();
}
