/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirections1.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfellahi <sfellahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 11:04:47 by ilchahbi          #+#    #+#             */
/*   Updated: 2024/10/09 18:24:06 by sfellahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell1.h"

char	*ft_strdup1(const char *s1)
{
	char	*dup;
	size_t	len;
	size_t	i;

	if (!s1)
		return (NULL);
	len = ft_strlen(s1);
	dup = (char *)malloc((len + 1) * sizeof(char));
	if (!dup)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		dup[i] = s1[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

void	init_reds(int *i, int *write_index, int *input_error)
{
	*i = 0;
	*write_index = 0;
	*input_error = 0;
}

int	handle_redirections(char **args, int *fd_out, int *fd_in)
{
	int	i;
	int	write_index;
	int	input_error;

	init_reds(&i, &write_index, &input_error);
	while (args[i] != NULL && !input_error)
	{
		if (ft_strcmp(args[i], ">") == 0 || ft_strcmp(args[i], ">>") == 0
			|| ft_strcmp(args[i], "<") == 0)
		{
			input_error = process_redirection(args, fd_in, fd_out, i);
			free(args[i]);
			args[i] = NULL;
			if (args[i + 1])
				free(args[i + 1]);
			if (args[i + 1])
				i += 2;
		}
		else
			args[write_index++] = args[i++];
	}
	if (input_error)
		free_reds(args, i);
	args[write_index] = NULL;
	return (input_error);
}

void	create_new_env(t_env **env_list, char *name, char *value)
{
	t_env	*new_node;

	new_node = malloc(sizeof(t_env));
	if (new_node)
	{
		new_node->key = ft_strdup1(name);
		if (value)
			new_node->value = ft_strdup1(value);
		else
			new_node->value = ft_strdup1("");
		new_node->exported = 1;
		new_node->next = NULL;
		ft_lstadd_back(env_list, new_node);
	}
}
