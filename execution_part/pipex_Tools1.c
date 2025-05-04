/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_Tools1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilchahbi <ilchahbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 06:04:19 by sfellahi          #+#    #+#             */
/*   Updated: 2024/10/06 12:32:35 by ilchahbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell1.h"

char	*find_and_check_path(char **all_path, char *cmd)

{
	char	*final_path;
	int		i;

	i = 0;
	while (all_path[i] != NULL)
	{
		final_path = check_and_build_path(all_path[i], cmd);
		if (final_path != NULL)
			return (final_path);
		i++;
	}
	return (NULL);
}

char	*find_the_right_path(char *cmd, char *env[])

{
	char	**all_path;
	char	*final_path;
	char	*full_path_check;

	all_path = NULL;
	final_path = NULL;
	full_path_check = check_full_path(cmd);
	if (full_path_check != NULL)
		return (full_path_check);
	all_path = extract_paths(env);
	if (all_path == NULL)
		return (NULL);
	final_path = find_and_check_path(all_path, cmd);
	return (final_path);
}

void	execute(char *argv, char **envp)

{
	char	**cmd;
	char	*path;

	cmd = ft_split(argv, '\a');
	path = find_the_right_path(cmd[0], envp);
	if (!path)
	{
		handle_error();
	}
	if (execve(path, cmd, envp) == -1)
		handle_error();
}
