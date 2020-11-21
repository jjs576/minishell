# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jjoo <jjoo@student.42seoul.kr>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/20 12:58:35 by jjoo              #+#    #+#              #
#    Updated: 2020/11/21 14:31:17 by jjoo             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	minishell
CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror
SRCS	=	$(wildcard srcs/*.c)
INCS	=	-I includes -I libft -I ft_printf/includes -I get_next_line
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
