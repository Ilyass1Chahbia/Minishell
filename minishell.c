/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfellahi <sfellahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 01:41:11 by ilchahbi          #+#    #+#             */
/*   Updated: 2024/10/15 23:47:45 by sfellahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_sg;

void	sign_fun(int sgn)
{
	if (sgn == SIGINT)
	{
		made_printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		g_sg = 1;
		ft_exit_code(1, 1);
	}
}

void	signal_func(void)
{
	signal(SIGINT, sign_fun);
	signal(SIGQUIT, SIG_IGN);
	rl_catch_signals = 0;
}

int	big_process(t_tower *tower, t_env **envi)
{
	spc_reds(tower);
	space_tab(tower);
	handle_dollars(tower);
	hide_dilemeter(tower);
	revert_dilemeter(tower);
	init_fd_heredoc(tower);
	if (open_herdoc(tower, envi) <= 0)
		return (0);
	dollar_check(tower);
	big_expand(tower, envi);
	rev_dollars(tower);
	revert_dollars(tower);
	ambigious_warn(tower);
	special_cases(tower);
	fill_xp(tower);
	skip_while(tower);
	return (1);
}

int	ft_exit_code(int x_c, int n)
{
	static int	res;

	if (n == 0)
		return (res);
	else
	{
		res = x_c;
	}
	return (0);
}

int	main(int ac, char **av, char **env)
{
	t_tower		*tower;
	int			n;

	n = 0;
	if (!isatty(STDIN_FILENO))
	{
		made_printf("Mini$hell doesn't take arguments!!!\n");
		exit(1);
	}
	(void)ac;
	(void )av;
	tower = NULL;
	signal_func();
	n = big_loop(tower, env);
	return (n);
}
