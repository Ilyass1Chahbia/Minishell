/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilchahbi <ilchahbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 06:02:24 by sfellahi          #+#    #+#             */
/*   Updated: 2024/10/13 12:54:18 by ilchahbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell1.h"

static void	handle_input_redirection(char **args, int *i, int *fd_in)
{
	if (args[*i + 1])
	{
		*fd_in = open(args[*i + 1], O_RDONLY);
		if (*fd_in == -1)
		{
			perror("open");
			exit(EXIT_FAILURE);
		}
		dup2(*fd_in, STDIN_FILENO);
		close(*fd_in);
	}
	ft_memmove(&args[*i], &args[*i + 2],
		sizeof(char *) * (ft_array_len(args) - *i - 1));
	(*i)--;
}

void	handle_redirections1(char **args, int *fd_out, int *fd_in)
{
	int	i;

	i = 0;
	while (args[i])
	{
		if (ft_strcmp(args[i], ">") == 0 || ft_strcmp(args[i], ">>") == 0)
			handle_output_redirection(*args, &i, *fd_out);
		else if (ft_strcmp(args[i], "<") == 0)
			handle_input_redirection(args, &i, fd_in);
		i++;
	}
}

int	is_empty_or_undefined_var(char *arg)
{
	if (!arg || arg[0] == '\0')
		return (1);
	if (arg[0] == '$')
		return (1);
	return (0);
}

int	is_special_token(char *arg)
{
	if (!arg)
		return (0);
	if (ft_strncmp(arg, "<<", 2) == 0
		|| ft_strncmp(arg, ">>", 2) == 0
		|| ft_strncmp(arg, ">", 1) == 0
		|| ft_strncmp(arg, "<", 1) == 0)
		return (1);
	return (0);
}

void	handle_command_not_found1(char *cmd)
{
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": command Not found\n", 2);
	ft_exit_code(127, 1);
	exit(127);
}
