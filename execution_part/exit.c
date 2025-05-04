/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilchahbi <ilchahbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 05:06:14 by sfellahi          #+#    #+#             */
/*   Updated: 2024/10/14 19:03:44 by ilchahbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell1.h"

void	free_env_list(t_env *env_list)
{
	t_env	*current;
	t_env	*next;

	current = env_list;
	while (current != NULL)
	{
		next = current->next;
		if (current->key)
			free(current->key);
		if (current->value)
			free(current->value);
		free(current);
		current = next;
	}
}

static int	is_valid_number(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i])
	{
		if (!isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	handle_exit_args(char **args)
{
	if (!is_valid_number(args[1]))
	{
		ft_putstr_fd("exit: ", 2);
		ft_putstr_fd(args[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		return (255);
	}
	else if (args[2])
	{
		ft_putstr_fd("exit: too many arguments\n", 2);
		ft_exit_code(1, 1);
		return (-1);
	}
	return (ft_atoi(args[1]));
}

void	ft_exit(char **args, t_env **env_list, int f)
{
	int	exit_code;
	int	k;

	exit_code = 0;
	k = 0;
	if (args && args[1])
	{
		k = 1;
		exit_code = handle_exit_args(args);
		if (exit_code == -1)
			return ;
	}
	free_env_list(*env_list);
	clear_history();
	if (f == 0)
		made_printf("exit\n");
	if (k != 1)
		exit_code = ft_exit_code(1, 0);
	exit(exit_code);
}

void	replace_spaces_if_full(char **str)
{
	int		is_full_of_spaces;
	char	*p;

	is_full_of_spaces = 1;
	p = *str;
	while (*p != '\0')
	{
		if (!ft_isspace((unsigned char)*p))
		{
			is_full_of_spaces = 0;
			break ;
		}
		p++;
	}
	if (is_full_of_spaces)
		ft_strcpy1337(*str, " ");
}
