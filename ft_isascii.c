/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfellahi <sfellahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 10:17:55 by ilchahbi          #+#    #+#             */
/*   Updated: 2024/10/09 11:48:58 by sfellahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isascii(int c)
{
	if (c >= 000 && c <= 0177)
		return (1);
	else
		return (0);
}

int	ft_strchr1337(const char *s, int c)
{
	int		i;
	char	ch;

	ch = (char) c;
	i = 0;
	while (s[i])
	{
		if (s[i] == ch)
			return (i);
		i++;
	}
	if (s[i] == ch)
		return (i);
	return (0);
}

char	*spc_btwn_qt(char *str)
{
	t_qt_state	state;
	char		*result;
	int			len;

	len = ft_strlen(str);
	ft_init_vars(&state);
	result = mark_sweep(NULL, (len + 1), -1);
	if (!result)
		return (NULL);
	while (str[state.i] != '\0')
	{
		process_char(result, str, &state);
		state.i++;
	}
	if (state.j > 0 && result[state.j - 1] == ' ')
		state.j--;
	result[state.j] = '\0';
	return (result);
}

void	echo_tower(t_tower *tower)
{
	t_info	*node;

	node = tower->top;
	while (node)
	{
		if (node->type == ARG && !ft_strcmp1337(node->data, "echo")
			&& (node->next != NULL && node->next->type == SPC)
			&& (node->next->next != NULL && node->next->next->type == DLR))
		{
			node->next->next->data = spc_btwn_qt(node->next->next->data);
		}
		node = node->next;
	}
}

void	free_garbage(t_grb *hood, t_grb *prev)
{
	while (hood)
	{
		prev = hood;
		hood = hood->next;
		free(prev->load);
		free(prev);
	}
}
