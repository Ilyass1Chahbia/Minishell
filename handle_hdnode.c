/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_hdnode.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfellahi <sfellahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 11:22:00 by ilchahbi          #+#    #+#             */
/*   Updated: 2024/10/15 23:51:37 by sfellahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_node_herdoc(t_node_context *context, int *n)
{
	char	*del;

	del = NULL;
	if (handle_herdoc(context->node, context->env, context->fd, &del))
	{
		close_fd_leak(context->tower);
		return (1);
	}
	ft_save_here_doc(context->fd[0], context->tower, *(context->l));
	context->tower->top->fd_pipee[*n] = context->fd[0];
	close(context->fd[1]);
	return (0);
}
