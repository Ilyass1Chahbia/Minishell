/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_single_command_utils3.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfellahi <sfellahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 11:19:21 by sfellahi          #+#    #+#             */
/*   Updated: 2024/10/15 23:30:25 by sfellahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell1.h"

void	handle_command_not_found(char **args)
{
	replace_spaces_if_full(&args[0]);
	if ((!(ft_strcmp(args[0], "<<") == 0)) || only_whitespace(*args))
	{
		ft_putstr_fd("Command Not Found: ", 2);
		ft_putendl_fd(args[0], 2);
		ft_exit_code(127, 1);
	}
}

static char	*get_command_path(char **args, char **cmnd,
	t_env **env_list, int *n)
{
	char	*path;

	path = NULL;
	if (args[0] && ft_strchr(args[0], '/'))
		path = args[0];
	else if (args[0] && ft_strcmp(args[0], "minishell") == 0)
		path = "./minishell";
	else
		path = find_command_path(args, cmnd, env_list, n);
	return (path);
}

static void	execute_and_exit(char *path, t_pvar *ss,
	t_env **env_list, int n)
{
	execute_command(path, ss, env_list, n);
	if (path != ss->args[0])
		free(path);
	exit(0);
}

void	child_process(char **args, char **cmnd, t_env **env_list)
{
	char	*path;
	int		n;
	t_pvar	ss;

	n = 0;
	path = get_command_path(args, cmnd, env_list, &n);
	if (path)
	{
		ss.args = remove_any_character(args, ' ');
		ss.cmnd = remove_any_character(cmnd, '\a');
		execute_and_exit(path, &ss, env_list, n);
	}
	else
	{
		handle_command_not_found(args);
		exit(127);
	}
}

void	handle_output_redirection(char *filename, int *fd_out, int flags)
{
	int	new_fd;

	new_fd = open(filename, flags, 0644);
	if (new_fd == -1)
	{
		perror("open");
		return ;
	}
	if (*fd_out != -1)
		close(*fd_out);
	*fd_out = new_fd;
}
