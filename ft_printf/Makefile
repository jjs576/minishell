# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jjoo <jjoo@student.42seoul.kr>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/07/25 16:05:03 by jjoo              #+#    #+#              #
#    Updated: 2020/11/21 14:37:10 by jjoo             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	libftprintf.a
CC			=	gcc
CFLAGS		=	-Wall -Wextra -Werror

INCS		=	includes
SRCS		=	srcs/ft_printf.c srcs/output_num.c srcs/output_type.c\
				srcs/output_utils.c srcs/parser.c srcs/utils.c
OBJS		=	$(SRCS:.c=.o)

AR			=	ar
ARFLAGS		=	-rcs

.c.o: $(SRCS)
	$(CC) $(CFLAGS) -c $< -o $@ -I $(INCS)

$(NAME): $(OBJS)
	$(AR) $(ARFLAGS) $(NAME) $(OBJS)

all: $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

bonus: all

re: fclean all
