/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_single_command_utils.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilchahbi <ilchahbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 14:58:23 by sfellahi          #+#    #+#             */
/*   Updated: 2024/10/06 10:52:26 by ilchahbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell1.h"

void	free_string_array(char **array)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	free_string_array2(char **array)
{
	int	i;
	int	n;

	if (!array)
		return ;
	i = 0;
	n = 0;
	while (array[n])
	{
		n++;
	}
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

int	is_directory(const char *path)
{
	struct stat	path_stat;

	if (stat(path, &path_stat) != 0)
		return (0);
	return (S_ISDIR(path_stat.st_mode));
}

int	ft_array_len(char **array)
{
	int	len;

	len = 0;
	while (array[len] != NULL)
		len++;
	return (len);
}
