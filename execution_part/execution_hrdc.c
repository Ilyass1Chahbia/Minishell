/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_hrdc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilchahbi <ilchahbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 11:58:10 by ilchahbi          #+#    #+#             */
/*   Updated: 2024/10/11 11:03:52 by ilchahbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell1.h"

static char	*handle_no_heredoc(char **result, int *i)
{
	char	*final;

	if (!result || !result[*i])
		return (NULL);
	final = ft_strdup1(result[*i]);
	if (!final)
		return (NULL);
	(*i)++;
	return (final);
}

static char	*handle_heredoc(char **result, int *i)
{
	char	*final;

	if (!result || !result[*i])
		return (NULL);
	final = ft_strdup1("\a");
	if (!final)
		return (NULL);
	if (result[*i] && !ft_strcmp(result[*i], "<<"))
	{
		if (result[*i + 1])
			*i += 2;
		else
			(*i)++;
	}
	else
		(*i)++;
	return (final);
}

static char	*join_strings(char *s1, char *s2)
{
	char	*temp;
	char	*result;

	temp = s1;
	result = ft_strjoin(s1, s2);
	free(temp);
	return (result);
}

static char	*process_result(char **result, int i, char *final)
{
	char	*temp;

	if (!result || !final)
		return (NULL);
	while (result[i])
	{
		if (!ft_strstr(result[i], "<<"))
		{
			temp = join_strings(final, "\a");
			if (!temp)
				return (NULL);
			final = join_strings(temp, result[i]);
			if (!final)
				return (NULL);
		}
		else if (result[i] && !ft_strcmp(result[i], "<<"))
		{
			if (result[i + 1])
				i++;
		}
		i++;
	}
	return (final);
}

char	*remove_heredocs(char *input)
{
	char	**result;
	char	*final;
	int		i;

	if (!input)
		return (NULL);
	i = 0;
	result = ft_split(input, '\a');
	if (!result || !result[0])
	{
		if (result)
			ft_free_array(result);
		return (ft_strdup1(""));
	}
	if (!ft_strstr(result[i], "<<"))
		final = handle_no_heredoc(result, &i);
	else
		final = handle_heredoc(result, &i);
	if (!final)
		return (ft_free_array(result), NULL);
	final = process_result(result, i, final);
	ft_free_array(result);
	if (!final)
		return (ft_strdup1(""));
	return (final);
}
