/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_Tools2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilchahbi <ilchahbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 06:05:17 by sfellahi          #+#    #+#             */
/*   Updated: 2024/10/16 09:41:53 by ilchahbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell1.h"

char	*remove_a_character(const char *str)
{
	int		i;
	int		j;
	char	*new_str;

	if (!str)
		return (NULL);
	new_str = (char *)malloc(sizeof(char) * (count_printable_chars(str) + 1));
	if (!new_str)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (ft_isprint(str[i]))
			new_str[j++] = str[i];
		i++;
	}
	new_str[j] = '\0';
	return (new_str);
}

char	*check_and_build_path(char *path, char *command)
{
	char	*full_path;
	char	*final_path;
	char	*cmd;
	char	*dmc;

	cmd = remove_a_character(command);
	dmc = ft_strjoin("/", cmd);
	if (!dmc)
		return (free(cmd), NULL);
	if (access(dmc, F_OK | X_OK) == 0)
		return (free(cmd), dmc);
	free(dmc);
	full_path = ft_strjoin(path, "/");
	if (full_path == NULL)
		return (free(cmd), NULL);
	final_path = ft_strjoin(full_path, cmd);
	if (final_path == NULL)
		return (free(full_path), free(cmd), NULL);
	if (access(final_path, F_OK | X_OK) == 0)
		return (free(full_path), free(cmd), final_path);
	return (free(full_path), free(final_path), free(cmd), NULL);
}

char	**env_list_to_array(t_env *env_list)
{
	int		count;
	char	**env_array;
	t_env	*current;

	count = 0;
	current = env_list;
	while (current)
	{
		count++;
		current = current->next;
	}
	env_array = (char **)mark_sweep(NULL, (sizeof(char *) * (count + 1)), -1);
	if (!env_array)
		return (NULL);
	current = env_list;
	count = 0;
	while (current)
	{
		env_array[count] = ft_strjoin(current->key, "=");
		env_array[count] = ft_strjoin_free(env_array[count], current->value);
		current = current->next;
		count++;
	}
	env_array[count] = NULL;
	return (env_array);
}

void	free_pipeline(t_pipeline *pipeline)
{
	int	i;

	if (!pipeline)
		return ;
	i = 0;
	while (i < pipeline->cmd_count)
	{
		cleanup_command(&pipeline->commands[i]);
		i++;
	}
	free(pipeline->commands);
	pipeline->commands = NULL;
	pipeline->cmd_count = 0;
}
