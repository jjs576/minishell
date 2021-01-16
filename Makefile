# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jjoo <jjoo@student.42seoul.kr>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/20 12:58:35 by jjoo              #+#    #+#              #
#    Updated: 2021/01/16 18:03:44 by jjoo             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	minishell
CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror
SRCS	=	srcs/command.c srcs/env_manager.c srcs/env.c srcs/error.c\
			srcs/execute_utils.c srcs/execute.c srcs/fd_handler.c\
			srcs/ft_cd.c srcs/ft_echo.c srcs/ft_env.c srcs/ft_exit.c\
			srcs/ft_export.c srcs/ft_pwd.c srcs/ft_unset.c srcs/get_next_line.c\
			srcs/input_replacer.c srcs/main.c srcs/prompt.c\
			srcs/signal_handler.c srcs/token_to_command.c srcs/token.c\
			srcs/tokenize.c srcs/utils.c
INCS	=	-I includes -I libft -I ft_printf/includes
OBJS	=	$(SRCS:.c=.o)
LIBFT	=	libft/libft.a
PRINTF	=	ft_printf/libftprintf.a
LFT		=	-L libft -lft
LPRINTF	=	-L ft_printf -lftprintf

all : $(NAME)

$(NAME) : $(LIBFT) $(PRINTF) $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LFT) $(LPRINTF) $(INCS)

$(LIBFT) :
	@make -C libft/

$(PRINTF) :
	@make -C ft_printf/

.c.o :
	$(CC) $(CFLAGS) -c $< -o $@ $(INCS)

clean :
	@make clean -C libft/
	@make clean -C ft_printf/
	rm -rf $(OBJS)

fclean : clean
	@make fclean -C libft/
	@make fclean -C ft_printf/
	rm -rf $(NAME)

re : fclean all
