/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_single_command_utils2.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilchahbi <ilchahbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 11:13:28 by sfellahi          #+#    #+#             */
/*   Updated: 2024/10/09 10:50:41 by ilchahbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell1.h"

int	handle_output_redirection1(char *file, int *fd_out, int flags)
{
	*fd_out = open(file, flags, 0644);
	if (*fd_out == -1)
	{
		perror("open");
		ft_exit_code(126, 1);
		return (1);
	}
	return (0);
}

int	handle_input_redirection1(char *file, int *fd_in)
{
	*fd_in = open(file, O_RDONLY);
	if (*fd_in == -1)
	{
		perror(file);
		ft_exit_code(126, 1);
		return (1);
	}
	return (0);
}

int	handle_output_redirect(char **args, int *fd_out, int i)
{
	int	flags;

	if (args[i + 1][0] == '\x12' || args[i + 1][0] == '\0')
		return (ft_putstr_fd("ambiguous redirect\n", 2),
			ft_exit_code(1, 1), 1);
	flags = O_WRONLY | O_CREAT;
	if (ft_strcmp(args[i], ">>") == 0)
		flags |= O_APPEND;
	else
		flags |= O_TRUNC;
	if (*fd_out != -1)
	{
		close(*fd_out);
		*fd_out = -1;
	}
	return (handle_output_redirection1(args[i + 1], fd_out, flags));
}

int	handle_input_redirect(char **args, int *fd_in, int i)
{
	if (args[i + 1][0] == '\x12' || args[i + 1][0] == '\0')
		return (ft_putstr_fd("ambiguous redirect\n", 2),
			ft_exit_code(1, 1), 1);
	if (*fd_in != -1)
	{
		close(*fd_in);
		*fd_in = -1;
	}
	return (handle_input_redirection1(args[i + 1], fd_in));
}

int	process_redirection(char **args, int *fd_in, int *fd_out, int i)
{
	if (args[i + 1] == NULL)
	{
		ft_putstr_fd("minishell: No such file or directory\n", 2);
		return (ft_exit_code(1, 1), 1);
	}
	if (ft_strcmp(args[i], ">") == 0 || ft_strcmp(args[i], ">>") == 0)
		return (handle_output_redirect(args, fd_out, i));
	else if (ft_strcmp(args[i], "<") == 0)
		return (handle_input_redirect(args, fd_in, i));
	return (0);
}
