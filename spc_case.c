/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spc_case.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilchahbi <ilchahbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 12:00:22 by ilchahbi          #+#    #+#             */
/*   Updated: 2024/09/08 12:00:51 by ilchahbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_init_vars(t_qt_state *state)
{
	state->in_single_quotes = 0;
	state->last_was_space = 1;
	state->i = 0;
	state->j = 0;
}

void	process_quote(char *result, char c, t_qt_state *state)
{
	state->in_single_quotes = !(state->in_single_quotes);
	result[state->j++] = c;
	state->last_was_space = 0;
}

void	process_whitespace(char *result, t_qt_state *state)
{
	if (state->in_single_quotes)
	{
		result[state->j++] = ' ';
	}
	else if (!(state->last_was_space))
	{
		result[state->j++] = ' ';
		state->last_was_space = 1;
	}
}

void	process_other(char *result, char c, t_qt_state *state)
{
	result[state->j++] = c;
	state->last_was_space = 0;
}

void	process_char(char *result, char *str, t_qt_state *state)
{
	char	c;

	c = str[state->i];
	if (c == '\'')
		process_quote(result, c, state);
	else if (c == 32 || (c >= 9 && c <= 13))
		process_whitespace(result, state);
	else
		process_other(result, c, state);
}
