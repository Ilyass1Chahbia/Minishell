/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilchahbi <ilchahbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 10:37:31 by ilchahbi          #+#    #+#             */
/*   Updated: 2024/10/15 11:12:11 by ilchahbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	x_c_heredoc(char **data, int n)
{
	char	*post;
	char	*pre;
	char	*xp;
	char	*hold;
	int		l;

	l = ft_strlen(data[0]);
	post = NULL;
	xp = NULL;
	hold = NULL;
	pre = NULL;
	if (data[0][0] == '$' && data[0][1] == '?' && data[0][2] == '\0')
	{
		data[0] = ft_strdup(ft_itoa2(ft_exit_code(0, 0)));
	}
	else if (data[0][n] == '$' && data[0][n + 1] == '?'
		&& data[0][n + 2] != '\0')
	{
		pre = ft_substr1337(data[0], 0, n);
		xp = ft_itoa2(ft_exit_code(0, 0));
		hold = ft_strjoin1337(pre, xp);
		post = ft_substr1337(data[0], n + 2, l - 2);
		hold = ft_strjoin1337(hold, post);
		data[0] = ft_strdup(hold);
	}
}

void	xpand_while(char **res, t_env **env)
{
	int	n;

	n = 0;
	while (res[0][n])
	{
		if (res[0][n] == '$')
		{
			if (ft_isdigit(res[0][n + 1]))
				replace_nm_heredoc(res, n);
			else if (res[0][n + 1] == '?')
			{
				x_c_heredoc(res, n);
			}
			else
			{
				mini_xpand(res, env, n);
			}
		}
		if (res[0][n] != '\0')
			n++;
	}
}

int	find_qts(char **res)
{
	int	l;

	l = ft_strlen(*res);
	if ((res[0][0] == '\'' || res[0][0] == '\"')
		&& (res[0][l - 1] == '\'' || res[0][l - 1] == '\"'))
		return (1);
	else
		return (0);
}

void	heredoc_qt(char **del)
{
	int		l;
	char	*tmp;

	l = ft_strlen(*del);
	tmp = NULL;
	if (!(*del))
		return ;
	if (find_qts(del))
	{
		tmp = ft_substr1337(*del, 1, l - 2);
		if (!tmp)
			*del = ft_strdup("\0");
		else
			*del = ft_strdup(tmp);
	}
}

int	inside_check(t_tower *tower, t_info *node, int *l)
{
	if (!handle_syntax_2(tower, node))
	{
		write(1, "Syntax Error\n", 13);
		return (-1);
	}
	if (node->type == PIPE)
	{
		(*l)++;
		tower->top->pipeee[*l] = mark_sweep(NULL, (sizeof(int) * 1), -1);
		if (!tower->top->pipeee[*l])
			return (-1);
		tower->top->pipeee[*l][0] = '\x011';
	}
	return (1);
}
