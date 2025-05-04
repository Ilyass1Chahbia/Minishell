/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfellahi <sfellahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 15:32:45 by sfellahi          #+#    #+#             */
/*   Updated: 2024/10/15 23:55:31 by sfellahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell1.h"

void	execution(char *input, t_env **env_list)
{
	char			*cleaned_input;
	char			**commands;
	int				cmd_count;
	struct termios	state;

	if (input == NULL)
	{
		made_printf("Mini$hell$: command not found\n");
		return (ft_exit_code(127, 1), (void)0);
	}
	cleaned_input = remove_heredocs(input);
	commands = split_commands(cleaned_input, &cmd_count);
	free(cleaned_input);
	if (!commands)
	{
		made_printf("Error: Failed to parse commands\n");
		return ;
	}
	tcgetattr(STDOUT_FILENO, &state);
	if (cmd_count == 1)
		execute_single_command(commands[0], env_list);
	else
		execute_pipeline(commands, cmd_count, env_list);
	tcsetattr(STDOUT_FILENO, TCSANOW, &state);
	free_commands(commands, cmd_count);
}

void	ft_free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

void	execute_builtin(char **args, t_env **env_list, int f)
{
	char	**cmnd_sp;

	cmnd_sp = ft_split(args[0], ' ');
	if (!ft_strcmp(args[0], "export"))
		ft_export(env_list, args);
	else if (!ft_strcmp(args[0], "echo"))
		ft_echo(args);
	else if (!ft_strcmp(args[0], "cd"))
		ft_cd(args, env_list);
	else if (!ft_strcmp(args[0], "pwd"))
		ft_pwd();
	else if (!ft_strcmp(args[0], "unset"))
		ft_unset(env_list, args);
	else if (!ft_strcmp(args[0], "ENV") || !(ft_strcmp(args[0], "env")))
		print_env(*env_list);
	else if (!ft_strcmp(args[0], "exit"))
		ft_exit(args, env_list, f);
	else if (!ft_strcmp(cmnd_sp[0], "export"))
		ft_export(env_list, cmnd_sp);
	ft_free_split(cmnd_sp);
}
