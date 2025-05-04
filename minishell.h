/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfellahi <sfellahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 01:41:21 by ilchahbi          #+#    #+#             */
/*   Updated: 2024/10/15 23:50:36 by sfellahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <limits.h>
# include <fcntl.h>
# include "execution_part/Minishell1.h"

typedef struct s_env	t_env;

enum	e_types
{
	REDIN = '<',
	REDOUT = '>',
	HERDOC = -2,
	APPND = 2,
	PIPE = '|',
	NLINE = '\n',
	SPC = 32,
	QT = '\'',
	DQT = '\"',
	DLR = '$',
	ARG = 10,
};

typedef struct s_info
{
	char			*data;
	enum e_types	type;
	struct s_info	*next;
	struct s_info	*previous;
	int				*heredoc_pipe;
	int				**pipeee;
	int				*fd_pipee;
}	t_info;

typedef struct s_tower
{
	t_info	*top;
	t_info	*bottom;
}	t_tower;

typedef struct s_grb
{
	void			*load;
	struct s_grb	*next;
}	t_grb;

typedef struct s_qt_state
{
	int	in_single_quotes;
	int	last_was_space;
	int	i;
	int	j;
}	t_qt_state;

typedef struct s_var
{
	t_info	*node;
	t_env	**ev;
	int		n;
	int		m;
	int		l;
	int		i;
	char	*xp;
	char	*old;
	char	*post;
	char	*hold;
	t_env	*tmp;
}	t_var;

typedef struct s_expand_data
{
	char	**res;
	t_env	**ev;
	char	*pre;
	char	*xp;
	int		n;
}	t_expand_data;

typedef struct s_node_context
{
	t_info	*node;
	t_tower	*tower;
	t_env	**env;
	int		fd[2];
	int		*l;
}	t_node_context;

void	ft_switchup(char *s);
int		ft_quote_mod(char *args);
void	free_func(char **args);
char	*ft_strdup(const char *src);
void	tower_addback(t_tower *tower, t_info *node);
t_info	*alloc_struct(char *data, enum e_types type);
int		not_like_us(char t);
void	close_fd_leak(t_tower *tower);
int		token_cases(t_tower *res, char *input, int n);
void	tower_init(t_tower *tower);
char	*ft_substr1337(char const *s, int start, int len);
int		ft_strlen(const char *s);
int		ft_isalnum1337(int c);
int		ft_isdigit1337(int c);
int		ft_strchr1337(const char *s, int c);
int		handle_syntax(t_tower *tower);
int		xp_check(t_info *node);
int		its_red(t_info *node);
int		post_heredoc(t_tower *tower, t_info *src);
void	hide_dilemeter(t_tower	*tower);
int		ft_isascii(int c);
void	ft_switch_qt(char *s);
void	init_fd_heredoc(t_tower *tower);
int		handle_node_herdoc(t_node_context *context, int *n);
void	ft_switch_dqt(char *s);
int		count_dollars(t_info *node);
void	handle_dollars(t_tower *tower);
int		ft_strcmp1337(const char *s1, const char *s2);
void	ft_strcpy1337(char *dst, const char *src);
void	big_expand(t_tower *tower, t_env **envi);
char	*ft_strjoin1337(char *s1, char const *s2);
void	revert_dilemeter(t_tower *tower);
void	revert_dollars(t_tower *tower);
int		open_herdoc(t_tower *tower, t_env **envi);
int		herdoc_syntax(t_info *node);
int		count_heredoc(t_info *node);
int		its_red_2(t_info *node);
int		pipe_check(t_info *node);
int		red_check(t_info *node);
int		check_arg(t_info *node);
int		handle_syntax_2(t_tower *tower, t_info *src);
void	skip_dqt(t_info **node);
void	skip_while(t_tower *tower);
void	echo_tower(t_tower *tower);
void	*mark_sweep(t_tower *tower, size_t len, int x);
char	*ft_itoa2(int nbr);
int		ft_exit_code(int x_c, int n);
t_tower	*token_nodes(char *input);
int		in_dqt(char *input, int n);
int		in_qt(char *input, int n);
int		reds_case1(t_tower *res, t_info *node, char *input, int n);
int		reds_case2(t_tower *res, t_info *node, char *input, int n);
int		dlr_case(char *input, int n);
void	ft_init_vars(t_qt_state *state);
void	process_char(char *result, char *str, t_qt_state *state);
void	under_cover(t_info	*node);
void	qts_check(t_info *node);
t_info	*qts_delim(t_info *node);
int		valid_nodes(t_info *node);
int		skip_qt(char *input, int n);
int		var_check(t_info *node);
void	skip_dqt(t_info **node);
void	replace_env_dqt(t_info *node, t_env **ev, int n);
void	replace_env(t_info *node, t_env **ev, int x);
void	replace_env_red(t_info *node, t_env **ev);
void	replace_nm(t_info *node);
void	env_case(int t, int x, t_info *node);
void	env_case_red(int t, t_info *node);
void	env_dqt_case(t_info *node, int n, int m, int l);
void	spc_reds(t_tower *tower);
void	x_c_xpand(t_info *node);
int		nt_xp(t_info *node);
void	xp_while1(t_info *node, t_env **env);
void	replace_nm_dqt(t_info *node, int n);
void	xp_while2(t_info *node, t_env **env);
void	xp_while3(t_info *node, t_env **env);
void	var_case1(t_info *node, t_env **env);
void	var_case2(t_info *node, t_env **env);
void	ft_switchback(t_info *node);
int		error_1(char *input);
char	*join_nodes(t_tower *tower, char *res);
void	error_2(t_tower *tower);
int		one_sp(t_tower *tower);
void	skip_while(t_tower *tower);
void	fix_space_pipe(t_info **node);
void	space_tab(t_tower *tower);
void	sign_fun(int sgn);
void	signal_func(void);
int		find_qts(char **res);
void	xpand_while(char **res, t_env **env);
void	mini_xpand(char **res, t_env **ev, int n);
void	heredoc_qt(char **del);
void	skip_one_dollar(t_info *node);
int		inside_check(t_tower *tower, t_info *node, int *l);
int		cal_lpipe(t_info *n);
void	ft_save_here_doc(int fd, t_tower *tw, int l);
void	ft_here_doc_cpy(int *s1, int *s2, int fd);
int		ft_cal_here_doc(int *p);
void	replace_nm_heredoc(char **res, int n);
int		is_delimiter(char c);
char	*get_prefix(const char *str, int n);
int		skip_to_end(const char *str, int n);
char	*get_expansion(const char *str, int start, int end);
int		handle_herdoc(t_info *node, t_env **env, int *fd, char **del);
int		initialize_pipes(t_tower *tower, int l);
int		handle_pipe_creation(t_tower *tower, int *l);
int		initialize_delimiter(t_info *node, char **del);
void	hrdoc_signal(int sn);
int		process_heredoc_input(t_info *node, char **del, int *fd, t_env **env);
int		big_loop(t_tower *tower, char **env);
int		big_process(t_tower *tower, t_env **envi);
void	free_garbage(t_grb *hood, t_grb *prev);
void	special_cases(t_tower *tower);
void	dollar_check(t_tower *tower);
void	rev_dollars(t_tower *tower);
void	ambigious_warn(t_tower *tower);
void	fill_xp(t_tower *tower);
void	move_sp(t_tower *tower);
char	*change_spc(char *str);
char	*while_del(t_info *node);
int		count_pipes(t_info *node);
int		cmp_check(char *res, char *del);
void	x_c_heredoc(char **data, int n);

#endif