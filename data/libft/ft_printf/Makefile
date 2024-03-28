# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fparis <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/09 15:04:07 by fparis            #+#    #+#              #
#    Updated: 2023/11/10 20:44:23 by fparis           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

CFLAGS = -Wall -Wextra -Werror

NAME = libftprintf.a

SRCS = ft_printf.c\
	ft_putchar_l.c\
	ft_putnbr_l.c\
	ft_putstr_l.c\
	ft_strlen.c\
	ft_putnbr_un.c\
	ft_ptrhexa.c\
	ft_putnbr_hexa.c


OBJS = $(SRCS:.c=.o)

HEADER = ../headers

all: $(NAME)

$(NAME): $(OBJS)
	ar -rcs $(NAME) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ -I $(HEADER)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
