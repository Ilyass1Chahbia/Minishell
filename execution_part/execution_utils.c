/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfellahi <sfellahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 11:44:23 by ilchahbi          #+#    #+#             */
/*   Updated: 2024/10/10 00:35:37 by sfellahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell1.h"

void	free_commands(char **commands, int cmd_count)
{
	while (cmd_count > 0)
		free(commands[--cmd_count]);
	free(commands);
}

char	**split_commands(char *input, int *cmd_count)
{
	char	**commands;

	*cmd_count = 0;
	commands = ft_split(input, '\e');
	while (commands[*cmd_count])
		(*cmd_count)++;
	return (commands);
}

int	only_whitespace(const char *str)
{
	while (*str)
	{
		if (!ft_isspace(*str))
			return (0);
		str++;
	}
	return (1);
}
