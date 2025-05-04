/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilchahbi <ilchahbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 11:48:10 by ilchahbi          #+#    #+#             */
/*   Updated: 2024/10/14 18:59:39 by ilchahbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell1.h"

void	check_input_validity(char **args, char **cmnd, t_env **env_list)
{
	if (!args || !args[0] || !cmnd || !cmnd[0])
		exit(1);
	if (is_empty_or_undefined_var(args[0]))
		exit(EXIT_SUCCESS);
	if (is_special_token(args[0]))
		exit(EXIT_SUCCESS);
	if (is_builtin(args[0]))
	{
		execute_builtin(args, env_list, 1);
		exit(EXIT_SUCCESS);
	}
}

t_args	prepare_arguments(char **args, char **cmnd)
{
	t_args	result;

	result.tr_arg = remove_any_character2(args, ' ');
	if (!result.tr_arg)
		exit(EXIT_FAILURE);
	result.tr_cmd = remove_any_character2(cmnd, '\a');
	if (!result.tr_cmd)
	{
		ft_free_array(result.tr_arg);
		exit(EXIT_FAILURE);
	}
	return (result);
}

void	find_and_execute_command(char **tr_arg, char **tr_cmd,
			char **args, t_env **env_list)
{
	char	*path;
	int		n;

	n = 0;
	path = find_the_right_path(tr_arg[0], env_list_to_array(*env_list));
	if (path)
		n = 1;
	if (n != 1)
		path = find_the_right_path(tr_cmd[0], env_list_to_array(*env_list));
	if (!path && n != 1)
		return (ft_free_array(tr_arg), ft_free_array(tr_cmd),
			handle_command_not_found1(args[0]), (void)0);
	if (n != 1)
		execve(path, tr_cmd, env_list_to_array(*env_list));
	else
		execve(path, tr_arg, env_list_to_array(*env_list));
	perror("execve");
	free(path);
	ft_free_array(tr_arg);
	ft_free_array(tr_cmd);
	exit(126);
}

void	execute_command1(char **args, char **cmnd, t_env **env_list)
{
	t_args	prepared_args;

	check_input_validity(args, cmnd, env_list);
	prepared_args = prepare_arguments(args, cmnd);
	find_and_execute_command(prepared_args.tr_arg, prepared_args.tr_cmd,
		args, env_list);
}
