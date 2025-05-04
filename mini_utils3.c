/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_utils3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfellahi <sfellahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 15:31:41 by ilchahbi          #+#    #+#             */
/*   Updated: 2024/10/15 23:49:09 by sfellahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	process_input(char *input, t_tower **tower)
{
	if (input[0] == '\0')
	{
		free(input);
		return (0);
	}
	if (*input)
		add_history(input);
	if (!error_1(input))
		return (0);
	ft_switchup(input);
	*tower = token_nodes(input);
	if (!*tower || one_sp(*tower))
		return (0);
	ft_switchback((*tower)->top);
	return (1);
}

int	handle_tower(t_tower *tower, t_env **envi)
{
	if (!handle_syntax(tower))
	{
		error_2(tower);
		return (0);
	}
	if ((big_process(tower, envi)) <= 0)
	{
		return (0);
	}
	return (1);
}

void	execute_part(char *res, t_env **envi, t_tower *tower)
{
	int	i;
	int	**fd;
	int	j;

	if (*envi)
	{
		(*envi)->pipeeee = tower->top->pipeee;
		(*envi)->fd_pipe1 = tower->top->fd_pipee;
	}
	execution(res, envi);
	i = -1;
	fd = tower->top->pipeee;
	while (fd[++i])
	{
		j = -1;
		while (fd[i][++j] != '\x011')
			close (fd[i][j]);
	}
}

int	big_loop(t_tower *tower, char **env)
{
	char	*input;
	char	*res;
	t_env	*envi;

	res = NULL;
	envi = NULL;
	init_env(&envi, env);
	while (1)
	{
		input = readline("Mini$hell$: ");
		if (!input)
			return (ft_lstclear(&envi, ft_del),
				printf("exit\n"), ft_exit_code(1, 0));
		if (process_input(input, &tower) == 0)
			continue ;
		if (handle_tower(tower, &envi) == 0)
			continue ;
		res = join_nodes(tower, res);
		execute_part(res, &envi, tower);
		mark_sweep(tower, 0, 1);
		res = NULL;
	}
	ft_lstclear(&envi, ft_del);
	return (0);
}
