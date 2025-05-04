/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd1.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilchahbi <ilchahbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 16:27:34 by sfellahi          #+#    #+#             */
/*   Updated: 2024/10/13 12:01:08 by ilchahbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell1.h"

char	*get_env_value(t_env *env_list, const char *key)
{
	while (env_list)
	{
		if (ft_strcmp(env_list->key, key) == 0)
			return (env_list->value);
		env_list = env_list->next;
	}
	return (NULL);
}

char	*expand_home(char *arg, char *home)
{
	static char	expanded_path[PATH_MAX];

	if (!home)
	{
		made_printf("cd: HOME not set\n");
		ft_exit_code(1, 1);
		return (NULL);
	}
	ft_strcpy(expanded_path, home);
	if (arg[1] == '/')
		ft_strcat(expanded_path, arg + 1);
	return (expanded_path);
}

void	fork_and_execute(int pipes[][2], char **commands
	, t_env **env_list, pid_t *pids)
{
	int	i;
	int	cmd_count;

	i = 0;
	cmd_count = ft_array_len(commands);
	(*env_list)->lastt = 0;
	while (i < cmd_count)
	{
		if (i == cmd_count - 1)
			(*env_list)->lastt = 1;
		signal(SIGINT, ft_signals_child);
		signal(SIGQUIT, SIG_DFL);
		pids[i] = fork();
		if (pids[i] == -1)
			return (perror("fork"), close_pipes(pipes, cmd_count), (void)0);
		else if (pids[i] == 0)
		{
			setup_child_pipes(pipes, i, cmd_count);
			close_other_pipes(pipes, i, cmd_count);
			execute_child_process(commands[i], env_list, i, cmd_count);
			exit(EXIT_FAILURE);
		}
		i++;
	}
	signal_func();
}

void	execute_pipeline(char **commands, int cmd_count, t_env **env_list)
{
	int		pipes[MAX_PIPES][2];
	pid_t	pids[MAX_PIPES + 1];
	int		last_status;

	if (!cmd_count)
		return ;
	if (cmd_count > MAX_PIPES + 1)
	{
		ft_putstr_fd("minishell: fork: Resource temporarily unavailable\n", 2);
		return ;
	}
	create_pipes(pipes, cmd_count);
	fork_and_execute(pipes, commands, env_list, pids);
	close_pipes(pipes, cmd_count);
	wait_for_children(pids, cmd_count, &last_status);
	ft_exit_code(last_status, 1);
}
