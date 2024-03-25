# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fparis <fparis@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/01 15:23:49 by fparis            #+#    #+#              #
#    Updated: 2024/03/25 00:05:30 by fparis           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -g -Wall -Wextra -Werror
NAME = so_long
HEADER = headers

SRCS = test.c\
		chunk.c\
		init.c\
		textures.c\
		items.c\
		init_anim.c\
		anim_manager.c\
		check_anim.c\
		init_textures.c\
		wall.c\
		flags.c\
		chunk_2.c\
		ui.c\
		interact.c\
		player.c\
		ui2.c\
		hide.c\
		free.c\
		free_2.c\
		parsing.c\
		init_game.c\
		pathfinding.c\
		chunk_3.c\
		utils.c\
		command.c\
		flags_2.c\
		wall_2.c\
		ui3.c\
		monster.c\
		monster_move.c\
		monster_move_2.c\
		monster_move_3.c\
		death.c\
		free_3.c\
		menu.c\
		buttons_functions.c\
		buttons_functions_2.c\
		buttons_functions_3.c\
		save.c\
		buttons_functions_4.c\
		buttons_functions_5.c\
		flags_3.c\
		flags_4.c\
		flags_5.c\
		flags_6.c\
		flags_7.c\
		sounds_manager.c\
		car.c\
		car_2.c\
		car_3.c\
		car_4.c

LIBFT = libft/libft.a libft/ft_printf/libftprintf.a
	
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $^ -o $(NAME) $(LIBFT) MacroLibX/libmlx.so -lSDL2 -I $(HEADER) -lm

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ -I $(HEADER)

$(LIBFT):
	@make printf -s -C libft

clean:
	rm -f $(OBJS) $(OBJS_BONUS)
	@make fclean -s -C libft

fclean: clean
	rm -f $(NAME)

re: fclean all
