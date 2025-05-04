/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_herdoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilchahbi <ilchahbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 11:19:10 by ilchahbi          #+#    #+#             */
/*   Updated: 2024/10/16 09:56:38 by ilchahbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	xp_check(t_info *node)
{
	if ((node->next != NULL && node->next->type == SPC
			&& node->next->next->type != DQT
			&& node->next->next->type != QT)
		|| (node->next->next != NULL && node->next->type != SPC
			&& node->next->type != DQT
			&& node->next->type != QT))
		return (1);
	else
		return (0);
}

int	process_heredoc_input(t_info *node, char **del, int *fd, t_env **env)
{
	char	*red;
	char	*res;

	heredoc_qt(del);
	while (1)
	{
		red = readline("> ");
		if (!ttyname(0))
			return (open("/dev/tty", O_RDWR), -1);
		if (!red)
			break ;
		res = ft_strdup(red);
		free(red);
		if (!res)
			return (-1);
		if (!cmp_check(res, *del))
			break ;
		if (xp_check(node))
			xpand_while(&res, env);
		ft_putstr_fd(res, fd[1]);
		ft_putstr_fd("\n", fd[1]);
	}
	return (0);
}

void	close_fd_leak(t_tower *tower)
{
	int	i;
	int	**fd;
	int	j;

	i = -1;
	fd = tower->top->pipeee;
	if (count_pipes(tower->top) == 0)
	{
		while (++i <= count_pipes(tower->top))
		{
			j = -1;
			while (fd[i][++j] != '\x011')
				close (fd[i][j]);
		}
	}
	else
	{
		while (++i < count_pipes(tower->top))
		{
			j = -1;
			while (fd[i][++j] != '\x011')
				close (fd[i][j]);
		}
	}
}

int	handle_node(t_node_context *context, t_tower *tower, int i, int *n)
{
	char	*del;

	del = NULL;
	if (!handle_syntax_2(context->tower, context->node))
	{
		write(1, "Syntax Error\n", 13);
		ft_exit_code(258, 1);
		i = 1;
	}
	if (context->node->type == PIPE)
	{
		(*n)++;
		if (handle_pipe_creation(context->tower, context->l))
			return (close_fd_leak(tower), 1);
	}
	else if (context->node->type == HERDOC)
	{
		if (handle_node_herdoc(context, n))
			return (1);
	}
	else if (context->node->type == REDIN)
		context->tower->top->fd_pipee[*n] = -1;
	if (i == 1)
		return (close_fd_leak(tower), 1);
	return (0);
}

int	open_herdoc(t_tower *tower, t_env **env)
{
	t_node_context	context;
	int				l;
	int				i;
	int				n;

	context.node = tower->top;
	l = cal_lpipe(context.node);
	if (initialize_pipes(tower, l))
		return (1);
	l = 0;
	n = 0;
	context.tower = tower;
	context.env = env;
	context.l = &l;
	while (context.node)
	{
		i = 0;
		if (handle_node(&context, tower, i, &n))
			return (-1);
		context.node = context.node->next;
	}
	signal(SIGINT, sign_fun);
	return (1);
}
