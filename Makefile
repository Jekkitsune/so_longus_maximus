# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fparis <fparis@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/01 15:23:49 by fparis            #+#    #+#              #
#    Updated: 2024/03/28 21:39:03 by fparis           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -g -Wall -Wextra -Werror
NAME = so_long
HEADER = data/headers

SRC_DIR = data
OBJ_DIR = data/obj

SRCS = main.c\
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
		car_4.c\
		anim_sounds.c\
		anim_sounds_2.c\
		monster_vision.c\
		buttons_functions_6.c\
		menu_2.c

LIBFT = data/libft/libft.a data/libft/ft_printf/libftprintf.a

OBJS = $(SRCS:%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	@$(CC) $(CFLAGS) $^ -o $(NAME) $(LIBFT) data/MacroLibX/libmlx.so -lSDL2 -I $(HEADER) -lm
	 @echo "$(NAME) compilation successful !"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	@echo "Compiling $(notdir $<)..."
	@$(CC) $(CFLAGS) -c $< -o $@ -I $(HEADER)

$(LIBFT):
	@make printf -s -C data/libft

clean:
	@echo "Removing object..."
	@rm -rf $(OBJ_DIR)
	@echo "Removing libft..."
	@make fclean -s -C data/libft

fclean: clean
	@echo "Removing $(NAME)..."
	@rm -f $(NAME)

re: fclean all

run: all
	./so_long levels/level_0.ber levels/level_1.ber levels/level_2.ber levels/level_3.ber levels/monster_test.ber levels/race.ber levels/Editor_map.ber

.PHONY: all clean fclean re run
