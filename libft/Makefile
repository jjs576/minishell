# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jjoo <jjoo@student.42seoul.kr>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/07/13 17:27:21 by jjoo              #+#    #+#              #
#    Updated: 2020/11/21 13:54:18 by jjoo             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	libft.a
CC			=	gcc
CFLAGS		=	-Wall -Wextra -Werror -I.

SRCS		=	ft_strchr.c ft_atoi.c ft_strdup.c ft_bzero.c ft_strjoin.c \
				ft_calloc.c ft_strlcat.c ft_isalnum.c ft_memccpy.c ft_strlcpy.c \
				ft_isalpha.c ft_memchr.c ft_strlen.c ft_isascii.c ft_memcmp.c \
				ft_strmapi.c ft_isdigit.c ft_memcpy.c ft_strncmp.c ft_isprint.c \
				ft_memmove.c ft_strnstr.c ft_itoa.c ft_memset.c ft_strrchr.c \
				ft_putchar_fd.c ft_strtrim.c ft_putendl_fd.c ft_substr.c \
			   	ft_putnbr_fd.c ft_tolower.c ft_putstr_fd.c ft_toupper.c ft_split.c
OBJS		=	$(SRCS:.c=.o)

BONUS		=	ft_lstnew.c ft_lstlast.c ft_lstsize.c ft_lstmap.c ft_lstiter.c \
				ft_lstadd_back.c ft_lstadd_front.c ft_lstclear.c ft_lstdelone.c
BONUS_OBJS	=	$(BONUS:.c=.o)

AR			=	ar
ARFLAGS		=	-rcs

.c.o: $(SRCS)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS) $(BONUS_OBJS)
	$(AR) $(ARFLAGS) $(NAME) $(OBJS) $(BONUS_OBJS)

all: $(NAME)

clean:
	rm -f $(OBJS) $(BONUS_OBJS)

fclean: clean
	rm -f $(NAME)

bonus: $(OBJS) $(BONUS_OBJS)
	$(AR) $(ARFLAGS) $(NAME) $(OBJS) $(BONUS_OBJS)

re: fclean all
