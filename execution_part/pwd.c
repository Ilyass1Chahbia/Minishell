/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfellahi <sfellahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 02:06:06 by sfellahi          #+#    #+#             */
/*   Updated: 2024/10/15 21:10:51 by sfellahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell1.h"

void	ft_pwd(void)

{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		made_printf("%s\n", cwd);
		ft_exit_code(0, 1);
	}
	else
	{
		made_printf("pwd: error retrieving directory: %s\n", strerror(errno));
		ft_exit_code(1, 1);
	}
}

void	free_env_array(char **env_array)
{
	int	i;

	i = 0;
	while (env_array[i])
	{
		free(env_array[i]);
		i++;
	}
	free(env_array);
}

void	ft_lstadd_front(t_env **lst, t_env *new)
{
	if (!lst || !new)
		return ;
	new->next = *lst;
	*lst = new;
}
