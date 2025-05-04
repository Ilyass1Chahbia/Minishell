/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Minishell1.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilchahbi <ilchahbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 08:02:03 by sfellahi          #+#    #+#             */
/*   Updated: 2024/10/14 19:00:03 by ilchahbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL1_H
# define MINISHELL1_H
# include "../minishell.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <sys/time.h>
# include <unistd.h>
# include <sys/stat.h>
# include <errno.h>
# include <math.h>
# include <stddef.h>
# include <limits.h>
# include <ctype.h>
# include <pthread.h>
# include <stdarg.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/errno.h>
# include <sys/param.h>
# include <signal.h>
# include <termios.h>
# include <stdint.h>
# define MAX_PIPES 1024

extern int	g_sg;

typedef struct s_env
{
	char			*key;
	char			*value;
	int				exported;
	int				**pipeeee;
	struct s_env	*next;
	int				original_stdinput;
	int				input_error_check;
	int				hidden;
	int				*fd_pipe1;
	int				lastt;
}	t_env;

typedef struct s_redirection
{
	int		type;
	char	*file;
	int		fd;
}	t_redirection;

typedef struct s_command
{
	char	**args;
	char	*input_file;
	char	*output_file;
	int		append_output;
	int		heredoc_fd;
}	t_command;

typedef struct s_pipeline
{
	t_command	*commands;
	int			cmd_count;
}	t_pipeline;

typedef struct s_command_info
{
	char	**args;
	char	**cmnd;
	int		fd_out;
	int		fd_in;
	int		original_stdout;
	int		original_stdin;
	int		return_value;
}	t_commandd_info;

typedef struct s_pvar
{
	char	**args;
	char	**cmnd;
	int		n;
}	t_pvar;

typedef struct s_args
{
	char	**tr_arg;
	char	**tr_cmd;
}	t_args;

int		ft_lstsize(t_env *lst);
void	ft_lstadd_back(t_env **lst, t_env *new);
void	ft_lstadd_front(t_env **lst, t_env *new);
void	ft_lstclear(t_env **lst, void (*del)(void*));
void	ft_del(void *data);
t_env	*ft_lstnew(void *content);
int		handle_redirections11(char **args, int *fd_out, int *fd_in);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strdup1(const char *s1);
char	*ft_strchr(const char *s, int c);
void	ft_lstdelone(t_env *lst, void (*del)(void *));
int		made_printf(const char *format, ...);
void	ft_echo(char **args);
char	**ft_split(char const *s, char c);
char	**ft_split2(char const *s, char c);
void	handle_no_equal(t_env **env_list, char *arg, int *n);
char	*remove_a_character(const char *str);
void	free_string_array2(char **array);
void	init_env(t_env **env_list, char **envp);
void	execution(char *temp, t_env **env_list);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);
int		compare_content(const void *content, const char *var_name);
size_t	ft_strlen1(const char *s);
void	ft_pwd(void);
char	*get_env_value(t_env *env_list, const char *key);
void	create_pipes(int pipes[][2], int cmd_count);
void	close_pipes(int pipes[][2], int cmd_count);
char	*expand_tilde(char *arg, t_env *env_list);
void	setup_child_pipes(int pipes[][2], int i, int cmd_count);
void	*ft_calloc(size_t count, size_t size);
void	ft_free_array(char **arr);
void	ft_unset(t_env **env_list, char **args);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	free_env_list(t_env *env_list);
void	print_env(t_env *env_list);
int		ft_isalnum(int c);
int		ft_isalpha(int c);
void	del_content(void *content);
int		is_valid_env_name(const char *name);
void	ft_cd(char **args, t_env **env_list);
void	update_env(t_env **env_list, const char *key, const char *value);
char	*ft_strcpy(char *s1, char *s2);
void	*ft_memcpy(void *dst, const void *src, size_t n);
char	*ft_strrchr(const char *s, int c);
size_t	ft_strlcat(char *dest, const char *src, size_t size);
char	*ft_strncat(char *dest, const char *src, size_t n);
char	*ft_strcat(char *dest, char *src);
char	*ft_strjoin(char const *s1, char const *s2);
void	ft_export(t_env **env_list, char **args);
void	print_sorted_env(t_env *env_list);
void	ft_sort_string_arr(char **arr);
char	*ft_strjoin_free(char *s1, char *s2);
int		ft_isdigit(int c);
char	*ft_strndup(const char *s, size_t n);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
void	execute_pipeline(char **commands, int cmd_count, t_env **env_list);
void	handle_error(void);
char	*ft_strtrim(char const *s1, char const *set);
void	*ft_memset(void *b, int c, size_t len);
char	*find_the_right_path(char *cmd, char *env[]);
char	*check_and_build_path(char *path, char *command);
char	*check_full_path(char *command);
char	**extract_paths(char *environment[]);
void	handle_input(char *input, t_env **env_list);
char	**env_list_to_array(t_env *env_list);
void	cleanup_command(t_command *cmd);
int		is_builtin(char *cmd);
void	ft_exit(char **args, t_env **env_list, int f);
int		ft_atoi(const char *str);
char	*ft_itoa(int n);
void	free_string_array(char **array);
void	execute_builtin(char **args, t_env **env_list, int f);
void	*ft_memmove(void *dest, const void *src, size_t n);
t_env	*ft_getenv(t_env *env_list, const char *name);
void	ft_putstr_fd(char *str, int fd);
void	ft_putendl_fd(char *s, int fd);
void	execute_single_command(char *cmd, t_env **env_list);
int		handle_redirections(char **args, int *fd_in, int *fd_out);
void	execute_command1(char **args, char **cmnd, t_env **env_list);
void	ft_putchar_fd(char c, int fd);
void	ft_print_here_doc(int *p);
int		ft_cal_here_doc(int *p);
t_env	*ft_lstnew_env(char *env_str, int hidden);
char	*ft_strstr(const char *haystack, const char *needle);
int		is_valid_identifier(const char *str);
void	ft_sort_string_arr(char **arr);
int		check(int a);
int		is_directory(const char *path);
int		len_of_number(long long n);
char	*str_new(size_t n);
size_t	char_check(char const *str, char const c);
size_t	strlenbysaad(const char *s);
int		ft_isprint(int c);
void	handle_output_redirection(char *filename, int *fd_out, int flags);
void	child_process(char **args, char **cmnd, t_env **env_list);
void	handle_child_process(char **args, char **cmnd, t_env **env_list);
int		ft_array_len(char **array);
void	close_other_pipes(int pipes[][2], int i, int cmd_count);
void	wait_for_children(pid_t *pids, int cmd_count, int *last_status);
void	execute_child_process(char *command, t_env **env_list,
			int pipe_index, int cmd_count);
char	*find_command_path(char **args, char **cmnd, t_env **env_list, int *n);
void	execute_command(char *path, t_pvar *ss,
			t_env **env_list, int n);
int		handle_output_redirection1(char *file, int *fd_out, int flags);
void	update_or_create_env(t_env **env_list, char *name, char *value,
			int append);
void	create_new_env(t_env **env_list, char *name, char *value);
void	free_env_array_partial(char **env_array, int count);
void	free_env_array(char **env_array);
void	print_env_array(t_env *env_list, char **env_array);
int		populate_env_array(t_env *env_list, char **env_array);
int		count_exported_env(t_env *env_list);
void	handle_plus_equal(t_env **env_list, char *arg, char *plus_equal);
int		is_quote(char c);
void	handle_quotes(char c, int *in_quotes, char *quote_char);
void	ft_signals_child(int sig);
void	execute_external_command(char **args, char **cmnd, t_env **env_list,
			int *return_ss);
void	clear(char **arr);
size_t	count_words(char const *s, char c);
void	replace_spaces_if_full(char **str);
int		skip_spaces(const char *str, int i, char c);
int		handle_quotes11(const char *str, int i, char *quote);
void	init_default_env(t_env **env_list);
void	process_env_variable(t_env **env_list, char *env_var,
			t_env **shlvl_node);
void	update_shlvl(t_env *shlvl_node);
void	cleanup_and_restore(t_commandd_info *info);
char	*remove_heredocs(char *input);
void	setup_redirections(int fd_in, int fd_out, t_env **env_list);
void	initialize_command_info(t_commandd_info *info, char *cmd);
void	setup_io(t_env **env_list, t_commandd_info *info);
void	cleanup_and_exit(t_commandd_info *info);
void	handle_command(t_commandd_info *info, t_env **env_list);
char	*expand_home(char *arg, char *home);
int		ft_isspace(int c);
void	handle_command_not_found(char **args);
void	handle_command_not_found1(char *cmd);
int		is_special_token(char *arg);
int		is_empty_or_undefined_var(char *arg);
int		process_redirection(char **args, int *fd_in, int *fd_out, int i);
int		only_whitespace(const char *str);
char	**split_commands(char *input, int *cmd_count);
void	free_command(char **commands);
void	free_commands(char **commands, int cmd_count);
int		is_builtin(char *cmd);
void	ft_free_split(char **split);
char	*process_heredocs(char *result, char *write, char *read, int in_quotes);
void	free_split(char **split, size_t count);
int		count_printable_chars(const char *str);
char	*check_full_path(char *command);
char	*find_the_right_path(char *cmd, char *env[]);
void	free_reds(char **args, int i);
void	ft_putnbr_fd(int n, int fd);
char	**remove_any_character(char **str, int c);
char	**remove_any_character2(char **str, int c);
void	ft_failsafe(char **res, int i);
char	**ft_split_spaces(char const *s);
#endif