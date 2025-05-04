/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirections11.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilchahbi <ilchahbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 11:28:09 by ilchahbi          #+#    #+#             */
/*   Updated: 2024/10/07 17:28:06 by ilchahbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell1.h"

void	free_reds(char **args, int i)
{
	while (args[i] != NULL)
	{
		free(args[i]);
		args[i] = NULL;
		i++;
	}
}

void	attempt_case(char **args, int *i)
{
	free(args[*i]);
	args[*i] = NULL;
	if (args[*i + 1])
	{
		free(args[*i + 1]);
		args[*i] = NULL;
		(*i) += 2;
	}
}

int	handle_redirections11(char **args, int *fd_out, int *fd_in)
{
	int	i;
	int	write_index;
	int	input_error;

	i = 0;
	write_index = 0;
	input_error = 0;
	while (args[i] != NULL && !input_error)
	{
		if (ft_strcmp(args[i], ">") == 0 || ft_strcmp(args[i], ">>") == 0
			|| ft_strcmp(args[i], "<") == 0)
		{
			input_error = process_redirection(args, fd_out, fd_in, i);
			attempt_case(args, &i);
		}
		else
			args[write_index++] = args[i++];
	}
	if (input_error)
		free_reds(args, i);
	args[write_index] = NULL;
	return (input_error);
}
