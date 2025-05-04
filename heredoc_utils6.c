/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils6.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfellahi <sfellahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 13:33:21 by ilchahbi          #+#    #+#             */
/*   Updated: 2024/10/15 23:54:47 by sfellahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	hrdoc_signal(int sn)
{
	if (sn == SIGINT)
	{
		close(0);
		ft_exit_code(1, 1);
	}
}

int	initialize_delimiter(t_info *node, char **del)
{
	if (node->next && node->next->type != SPC)
	{
		*del = while_del(node->next);
	}
	else if (node->next && node->next->type == SPC)
	{
		*del = while_del(node->next->next);
	}
	else
	{
		*del = NULL;
	}
	if (*del == NULL)
		return (1);
	return (0);
}

int	handle_herdoc(t_info *node, t_env **env, int *fd, char **del)
{
	if (pipe(fd))
		return (1);
	if (count_heredoc(node) >= 17)
	{
		printf("maximum here-document count exceeded\n");
		ft_lstclear(env, ft_del);
		mark_sweep(NULL, 0, 1);
		exit(2);
	}
	if (initialize_delimiter(node, del))
		return (close(fd[0]), close(fd[1]), 1);
	signal(SIGINT, hrdoc_signal);
	if (process_heredoc_input(node, del, fd, env) < 0)
		return (close(fd[0]), close(fd[1]), -1);
	return (0);
}

int	initialize_pipes(t_tower *tower, int l)
{
	int	j;

	j = -1;
	tower->top->pipeee = mark_sweep(NULL, (sizeof(int *) * (l + 1 + 1)), -1);
	if (!tower->top->pipeee)
		return (1);
	while (++j < (l + 1))
	{
		tower->top->pipeee[j] = mark_sweep(NULL, (sizeof(int) * 1), -1);
		if (!tower->top->pipeee[j])
			return (1);
		tower->top->pipeee[j][0] = '\x011';
	}
	tower->top->pipeee[l + 1] = NULL;
	return (0);
}

int	handle_pipe_creation(t_tower *tower, int *l)
{
	(*l)++;
	tower->top->pipeee[*l] = mark_sweep(NULL, (sizeof(int) * 1), -1);
	if (!tower->top->pipeee[*l])
		return (1);
	tower->top->pipeee[*l][0] = '\x011';
	return (0);
}
