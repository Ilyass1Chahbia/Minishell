/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilchahbi <ilchahbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 10:07:12 by ilchahbi          #+#    #+#             */
/*   Updated: 2024/09/09 15:01:07 by ilchahbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isalnum1337(int c)
{
	if ((c >= 48 && c <= 57) || (c >= 65 && c <= 90) || (c >= 97 && c <= 122)
		|| c == 95 || c == 63)
		return (1);
	else
		return (0);
}

int	ft_isdigit1337(int c)
{
	if (c >= 48 && c <= 57)
	{
		return (1);
	}
	else
		return (0);
}

int	dlr_case(char *input, int n)
{
	while (not_like_us(input[n]) && input[n] != '\0'
		&& input[n] != 47 && input[n] != 92)
	{
		n++;
		if (ft_isalnum1337(input[n]) && !ft_isalnum1337(input[n + 1]))
		{
			n++;
			break ;
		}
	}
	return (n);
}

int	its_red(t_info *node)
{
	if (!node)
		return (0);
	if (node->type == REDIN || node->type == REDOUT
		|| node->type == APPND)
		return (1);
	else
		return (0);
}

void	replace_nm(t_info *node)
{
	node->data = ft_strdup("\0");
}
