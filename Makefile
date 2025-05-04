# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ilchahbi <ilchahbi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/01 10:02:47 by ilchahbi          #+#    #+#              #
#    Updated: 2024/10/16 09:36:20 by ilchahbi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc

CFLAGS = -Wall -Wextra -Werror

LFLAG = -lreadline

READLINE_L = $(shell brew --prefix readline)/lib

READLINE_I = $(shell brew --prefix readline)/include

NAME = minishell

SRCS = minishell.c ft_switchup.c ft_quotes.c free_func.c alloc_utils.c token_utils.c str_utils.c xpand_utils2.c mini_utils.c heredoc_utils2.c heredoc_utils6.c mini_utils4.c handle_hdnode.c\
    ft_strdup.c lst_utils.c token_cases.c ft_substr.c ft_isalnum.c handle_syntax.c spc_case.c xpand_utils.c xpand_utils4.c heredoc_utils3.c heredoc_utils5.c dollars_utils.c\
    expand_utils.c ft_isascii.c expand_utils2.c the_xpand.c handle_herdoc.c heredoc_utils.c str_utils2.c xpand_utils3.c mini_utils2.c heredoc_utils4.c mini_utils3.c lst_utils2.c\
    ./execution_part/cd.c ./execution_part/cd_tools.c ./execution_part/echo.c ./execution_part/clear_line.c ./execution_part/clear_line2.c \
    ./execution_part/execution.c ./execution_part/exit.c ./execution_part/export.c ./execution_part/pipe_exec.c ./execution_part/spaces_split.c\
    ./execution_part/ft_env.c ./execution_part/libft_function.c ./execution_part/libft_function2.c \
    ./execution_part/libft_function3.c ./execution_part/libft_function4.c ./execution_part/libft_funtion5.c \
    ./execution_part/linked_list.c ./execution_part/made_printf.c ./execution_part/pwd.c \
    ./execution_part/unset_tools.c ./execution_part/unset.c ./execution_part/pipex.c \
    ./execution_part/pipex_Tools1.c ./execution_part/pipex_Tools2.c ./execution_part/pipex_Tools.c \
    ./execution_part/redirection.c ./execution_part/redirection_tools.c ./execution_part/execute_single_command.c ./execution_part/export_tools.c ./execution_part/linked_list2.c \
    ./execution_part/libft_function6.c ./execution_part/execution_single_command_utils.c ./execution_part/libft_function7.c  ./execution_part/execution_single_command_utils1.c \
    ./execution_part/execution_single_command_utils3.c ./execution_part/libft_function8.c ./execution_part/pipex_Tools3.c ./execution_part/execution_utils.c \
    ./execution_part/export_tools1.c ./execution_part/execution_single_command_utils2.c ./execution_part/pipex_Tools4.c ./execution_part/execution_hrdc.c ./execution_part/pipex_utils2.c \
    ./execution_part/pipex_Tools5.c ./execution_part/signals.c ./execution_part/libft_function9.c ./execution_part/ft_env1.c ./execution_part/pipex_utils1.c \
    ./execution_part/execute_single_commandd.c ./execution_part/execute_single_commanddd.c ./execution_part/execution1.c ./execution_part/execution_utils2.c \
    ./execution_part/execution2.c ./execution_part/cd1.c ./execution_part/handle_redirections1.c ./execution_part/handle_redirections11.c ./execution_part/env_utils.c
	
OBJCTS = $(SRCS:%.c=%.o)

HEADERS = minishell.h

all: $(NAME)

$(NAME): $(OBJCTS)
	$(CC) $(CFLAGS) $(OBJCTS) -o $@ -L $(READLINE_L) $(LFLAG)
%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -I $(READLINE_I) -c $< -o $@

clean:	
	rm -f $(OBJCTS) 

fclean : clean
	rm -f $(NAME) 

re : fclean all

.PHONY : all clean fclean re 