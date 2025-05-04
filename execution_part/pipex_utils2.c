/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilchahbi <ilchahbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 12:34:52 by ilchahbi          #+#    #+#             */
/*   Updated: 2024/10/06 13:36:28 by ilchahbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell1.h"

char	*check_full_path(char *command)
{
	if (command && (command[0] == '/'
			|| (command[0] == '.' && command[1] == '/')))
	{
		if (access(command, X_OK) == -1)
		{
			perror("access");
			exit(1);
		}
		return (command);
	}
	return (NULL);
}

char	**extract_paths(char *environment[])
{
	int	i;

	i = 0;
	while (environment[i] != NULL)
	{
		if ((ft_strncmp(environment[i], "PATH=", 5) == 0))
			return (ft_split(environment[i] + 5, ':'));
		i++;
	}
	return (NULL);
}

int	ft_isprint(int c)
{
	return ((c >= 32 && c <= 126) || c == '\0');
}

int	count_printable_chars(const char *str)
{
	int	i;
	int	new_len;

	i = 0;
	new_len = 0;
	while (str[i])
	{
		if (str[i] != '\a')
			new_len++;
		i++;
	}
	return (new_len);
}
