/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_Tools4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfellahi <sfellahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 11:40:55 by sfellahi          #+#    #+#             */
/*   Updated: 2024/09/18 12:54:16 by sfellahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell1.h"

void	cleanup_command(t_command *cmd)
{
	int	i;

	if (cmd == NULL)
		return ;
	if (cmd->args != NULL)
	{
		i = 0;
		while (cmd->args[i] != NULL)
		{
			free(cmd->args[i]);
			i++;
		}
		free(cmd->args);
	}
	if (cmd->input_file != NULL)
		free(cmd->input_file);
	if (cmd->output_file != NULL)
		free(cmd->output_file);
	cmd->args = NULL;
	cmd->input_file = NULL;
	cmd->output_file = NULL;
	cmd->append_output = 0;
}

void	create_pipes(int pipes[][2], int cmd_count)
{
	int	i;

	i = 0;
	while (i < cmd_count - 1)
	{
		if (pipe(pipes[i]) == -1)
		{
			perror("pipe");
			exit(EXIT_FAILURE);
		}
		i++;
	}
}
