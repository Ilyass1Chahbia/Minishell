/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_Tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilchahbi <ilchahbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 06:24:40 by sfellahi          #+#    #+#             */
/*   Updated: 2024/10/06 13:20:44 by ilchahbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell1.h"

static int	init_pipeline(t_pipeline *pipeline, char **commands)
{
	pipeline->cmd_count = 0;
	while (commands[pipeline->cmd_count])
		pipeline->cmd_count++;
	pipeline->commands
		= (t_command *)malloc(sizeof(t_command) * pipeline->cmd_count);
	if (!pipeline->commands)
		return (0);
	ft_memset(pipeline->commands, 0, sizeof(t_command) * pipeline->cmd_count);
	return (1);
}

static void	parse_redirections(char *command, t_command *cmd)
{
	char	*input_redirect;
	char	*output_redirect;

	cmd->input_file = NULL;
	cmd->output_file = NULL;
	cmd->append_output = 0;
	input_redirect = ft_strchr(command, '<');
	if (input_redirect)
	{
		*input_redirect = '\0';
		cmd->input_file = ft_strtrim(input_redirect + 1, " ");
	}
	output_redirect = ft_strchr(command, '>');
	if (output_redirect)
	{
		*output_redirect = '\0';
		cmd->output_file = ft_strtrim(output_redirect + 1, " ");
		if (*(output_redirect + 1) == '>')
			cmd->append_output = 1;
	}
}

static void	parse_commands(char **commands, t_pipeline *pipeline)
{
	int	i;

	i = 0;
	while (i < pipeline->cmd_count)
	{
		pipeline->commands[i].args = ft_split(commands[i], ' ');
		parse_redirections(commands[i], &pipeline->commands[i]);
		i++;
	}
}

void	free_command(char **commands)
{
	int	i;

	i = 0;
	while (commands[i])
	{
		free(commands[i]);
		i++;
	}
	free(commands);
}

void	parse_pipeline(char *input, t_pipeline *pipeline)
{
	char	**commands;

	commands = ft_split(input, '|');
	if (!commands)
	{
		pipeline->cmd_count = 0;
		pipeline->commands = NULL;
		return ;
	}
	init_pipeline(pipeline, commands);
	if (!pipeline->commands)
	{
		pipeline->cmd_count = 0;
		free_command(commands);
		return ;
	}
	parse_commands(commands, pipeline);
	free_command(commands);
}
