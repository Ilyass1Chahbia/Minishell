/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilchahbi <ilchahbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 00:56:02 by sfellahi          #+#    #+#             */
/*   Updated: 2024/10/14 12:21:00 by ilchahbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell1.h"

static void	print_arg(const char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == '\\' && arg[i + 1] == '\\')
		{
			write(STDOUT_FILENO, "\\", 1);
			i += 2;
		}
		else
		{
			write(STDOUT_FILENO, &arg[i], 1);
			i++;
		}
	}
}

static int	process_options(char **args, int *i)
{
	int	print_newline;
	int	j;

	print_newline = 1;
	while (args[*i] && args[*i][0] == '-')
	{
		if (ft_strcmp(args[*i], "-n") == 0)
		{
			print_newline = 0;
			(*i)++;
			continue ;
		}
		if (args[*i][1] != 'n')
			break ;
		j = 1;
		while (args[*i][j] == 'n')
			j++;
		if (args[*i][j] != '\0')
			break ;
		print_newline = 0;
		(*i)++;
	}
	return (print_newline);
}

void	ft_echo(char **args)
{
	int	i;
	int	print_newline;
	int	first_arg;

	i = 1;
	print_newline = process_options(args, &i);
	first_arg = 1;
	while (args[i])
	{
		if (!first_arg)
			write(STDOUT_FILENO, " ", 1);
		print_arg(args[i]);
		first_arg = 0;
		i++;
	}
	if (print_newline)
		write(STDOUT_FILENO, "\n", 1);
	ft_exit_code(0, 1);
}

void	handle_quotes(char c, int *in_quotes, char *quote_char)
{
	if (!*in_quotes)
	{
		*in_quotes = 1;
		*quote_char = c;
	}
	else if (c == *quote_char)
		*in_quotes = 0;
}

void	ft_failsafe(char **res, int i)
{
	while (i > 0)
	{
		i--;
		free(res[i]);
	}
	free(res);
}
