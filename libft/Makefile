# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fparis <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/01 11:50:04 by fparis            #+#    #+#              #
#    Updated: 2024/03/05 19:44:22 by fparis           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

CFLAGS = -Wall -Wextra -Werror

NAME = libft.a

HEADER = headers

SRCS =  ft_atoi.c\
	ft_isalpha.c\
	ft_memchr.c\
	ft_memset.c\
	ft_strlcpy.c\
	ft_strrchr.c\
	ft_bzero.c\
	ft_isascii.c\
	ft_memcmp.c\
	ft_strchr.c\
	ft_strlen.c\
	ft_tolower.c\
	ft_calloc.c\
	ft_isdigit.c\
	ft_memcpy.c\
	ft_strdup.c\
	ft_strncmp.c\
	ft_toupper.c\
	ft_isalnum.c\
	ft_isprint.c\
	ft_memmove.c\
	ft_strlcat.c\
	ft_strnstr.c\
	ft_substr.c\
	ft_strjoin.c\
	ft_strtrim.c\
	ft_split.c\
	ft_itoa.c\
	ft_strmapi.c\
	ft_striteri.c\
	ft_putchar_fd.c\
	ft_putstr_fd.c\
	ft_putendl_fd.c\
	ft_putnbr_fd.c\
	ft_lstnew.c\
	ft_lstadd_front.c\
	ft_lstsize.c\
	ft_lstlast.c\
	ft_lstadd_back.c\
	ft_lstdelone.c\
	ft_lstclear.c\
	ft_lstiter.c\
	ft_lstmap.c\
	get_next_line_utils.c\
	get_next_line.c\
	ft_strcmp.c\
	ft_middle_str.c\
	ft_intlen.c\
	ft_power.c\
	ft_revdigit.c\
	ft_max.c\
	ft_min.c


OBJS = $(SRCS:.c=.o)

FT_PRINTF = ft_printf/libftprintf.a

all: $(NAME)

$(NAME): $(OBJS)
	@ar -rcs $(NAME) $(OBJS)
	@echo Libft was compiled

$(FT_PRINTF):
	@make -s -C ft_printf

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@ -I $(HEADER)

printf: $(OBJS) $(FT_PRINTF)
	@ar -rcs $(NAME) $(OBJS) $(FT_PRINTF)
	@echo Libft and FT_printf were compiled
	
clean_printf:
	@make clean -s -C ft_printf

clean: clean_printf
	@rm -f $(OBJS)
	@echo Libft objects cleaned

fclean: clean clean_printf
	@rm -f $(NAME) $(FT_PRINTF)
	@echo Libft.a cleaned

re: fclean all

.PHONY: all clean fclean re bonus
