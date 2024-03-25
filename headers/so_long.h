/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 14:50:52 by fparis            #+#    #+#             */
/*   Updated: 2024/03/25 00:09:29 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "../libft/headers/libft.h"
# include "../MacroLibX/includes/mlx.h"
# include <stdlib.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>
# include <time.h>
# include <math.h>
# include <signal.h>
# include <sys/wait.h>

# define GROUND '0'
# define WALL '1'
# define ITEM 'C'
# define EXIT 'E'
# define HIDE 'H'
# define MONSTER 'M'
# define PLAYER 'P'

typedef struct s_path
{
	int				x;
	int				y;
	int				goal_x;
	int				goal_y;
	struct s_path	*next;
}	t_path;

typedef struct s_object
{
	void	*texture;
	int		size_x;
	int		size_y;
	char	*name;
	char	type;
	int		density;
}	t_object;

typedef struct s_animation
{
	void	**tab;
	int		size;
	int		index;
	char	*name;
	int		interval;
	int		clock;
}	t_animation;

typedef struct s_player
{
	int			x;
	int			y;
	int			base_speed;
	int			speed;
	int			is_running;
	int			movement[4];
	void		*sprite;
	void		*default_sprite;
	int			size_x;
	int			size_y;
	int			hitbox_x;
	int			hitbox_y;
	t_animation	*anim;
	t_animation	*current_anim;
	int			nb_anim;
	int			direction;
	int			can_interact;
	int			can_move;
	int			stun_timer;
	int			stamina;
	int			max_stamina;
	int			hidden;
	int			hidden_fr;
	int			dead;
}	t_player;

typedef struct s_monster
{
	int			x;
	int			y;
	int			size_x;
	int			size_y;
	int			center_x;
	int			center_y;
	int			base_speed;
	int			speed;
	int			direction;
	int			facing;
	void		*sprite;
	void		*default_sprite;
	t_animation	*anim;
	t_animation	*current_anim;
	int			nb_anim;
	int			exist;
	int			on_screen;
	int			follow_player;
	int			new_pos[2];
	int			last_pos[2];
	int			last_seen_x;
	int			last_seen_y;
}	t_monster;

typedef struct s_item
{
	t_object	*object;
	int			collected;
	int			x;
	int			y;
}	t_item;

typedef struct s_hideout
{
	t_object	*object;
	int			x;
	int			y;
}	t_hideout;

typedef struct s_UI
{
	int			hide;
	t_object	dark;
	t_object	shadow;
	t_object	big_shadow;
	t_object	interact;
	t_object	hide_ui;
	t_object	*light;
	t_object	*luminosity;
	t_object	red;
	int			is_dark;
	int			timer;
	t_object	*in_timer;
	int			in_timer_y;
	int			meters;
	int			movement;
	int			light_timer;
	int			in_anim;
	t_animation	heart_anim;
	void		*heart;
}	t_UI;

typedef	struct s_effect
{
	int			x;
	int			y;
	t_animation	*anim;
	int			anim_index;
	int			clock;
	void		*sprite;
}	t_effect;

typedef struct s_flags
{
	int			touhou;
	int			bad_apple_launched;
	int			old_tex;
	int			debug_mode;
	char		editor_tab[7];
	int			editor_index;
	int			editor_p_x;
	int			editor_p_y;
	int			editor_custom_exist;
	char		*editor_warning;
	int			editor_saved;
	int			fnaf;
	int			car;
	int			car_tab[2];
	int			car_delay[2];
	t_animation	explosion_anim;
	t_effect	*explosion_list;
	int			nb_explosion;
}	t_flags;

typedef struct s_data
{
	void			*mlx;
	void			*win;
	t_object		***map;
	t_object		***chunk;
	t_object		*objects;
	int				nb_objects;
	t_item			*items;
	t_hideout		*hideouts;
	t_player		player;
	int				nb_items;
	int				nb_hideout;
	int				item_collected;
	int				size_x;
	int				size_y;
	int				center_x;
	int				center_y;
	int				win_x;
	int				win_y;
	int				chunk_size;
	int				tex_size;
	int				exit_x;
	int				exit_y;
	void			*void_tex;
	t_UI			ui;
	t_flags			flags;
	char			*map_name;
	t_monster		monster;
	int				show_env;
	struct s_menu	*menu_list;
	struct s_menu	*current_menu;
	int				nb_menu;
	int				fullscreen;
	pid_t			music_pid;
	int				music_duration;
	int				music_full_duration;
	char			*current_music;
}	t_data;

typedef struct s_button
{
	char	*name;
	char	*selected_name;
	void	(*press)(t_data *data, int param);
}	t_button;

typedef struct s_menu
{
	t_button	*tab;
	int			button_index;
	int			margin;
	int			size;
	char		*name;
	void		(*menu_loop)(t_data *data);
}	t_menu;

void		move_chunk(t_data *data, int x, int y);
void		init_chunk_tab(t_data *data);
void		show_chunk(t_data *data);
void		init_data(t_data *data);
void		init_textures(t_data *data);
void		init_objects_tab(t_data *data);
t_object	*get_tex(t_data *data, char *name);
t_object	*get_object(t_data *data, char type);
void		init_items_tab(t_data *data);
void		add_item(t_data *data, int x, int y);
void		init_player_anim(t_data *data);
void		continue_player_anim(t_data *data);
void		change_anim(t_data *data, char *name, int reset);
int			get_anim_index(t_data *data, char *name);
int			is_idle(t_data *data, char *anim);
void		change_random_idle(t_data *data);
char		*get_random_anim(t_animation *tab, int start, int end);
char		*get_random_tex(t_object *tab, int start, int end);
t_object	*get_good_tex(t_data *data, int x, int y);
t_object	*get_wall(t_data *data, int x, int y);
void		move_anim(t_data *data);
void		idle_anim(t_data *data);
void		check_flags(t_data *data, char **argv);
void		check_wall(t_data *data, int *x, int *y);
void		show_obj(t_data *data, int i, int i2);
t_item		*has_item(t_data *data, int x, int y);
void		load_chunk(t_data *data, int x, int y);
int			tex_i(t_data *data, char *name);
void		init_bad_apple(t_data *data, t_animation *anim, int size);
void		continue_long_anim(t_data *data, t_animation *current, char *name);
void		init_ui(t_data *data);
t_object	*check_exit(t_data *data, int x, int y);
void		check_ui(t_data *data);
void		put_text(t_data *data, t_object *img, int y_shift, int time);
void		interact(t_data *data);
void		player_loop(t_data *data);
int			get_diff_player(t_data *data, int want_x);
void		show_nb_left(t_data *data);
void		init_hideouts_tab(t_data *data);
void		add_hideout(t_data *data, int x, int y);
t_hideout	*has_hideout(t_data *data, int x, int y);
void		hide(t_data *data);
void		stun_player(t_data *data, int time);
void		show_player(t_data *data);
void		show_interactible(t_data *data, int i, int i2);
int			get_diff_env(t_data *data, int want_x);
void		destroy_all_img(t_data *data);
void		free_all_data(t_data *data);
void		free_exit(t_data *data, char *error);
void		hideout_collision(t_data *data, int *x, int *y);
void		show_meters(t_data *data);
void		add_meters(t_data *data, int x, int y);
void		init_map(t_data	*data, char *map);
void		init_game(t_data *data);
int			key_down_manager(int key, void *param);
int			key_up_manager(int key, void *param);
int			game_loop(void *param);
void		is_correct_map(t_data *data);
int			can_go_to(t_data *data, int *coord_1, int *coord_2);
void		check_chunk_load(t_data *data);
int			is_type(t_data *data, int x, int y, char type);
int			in_bound(t_data *data, int x, int y);
void		bad_apple_manager(t_data *data);
void		debug_command(t_data *data, int key);
int			*get_coord(int res[2], int x, int y);
void		free_gnl(t_data *data, int fd, char *line);
void		init_more_ui(t_data *data);
void		show_light_anim(t_data *data);
void		screen_effect(t_data *data, t_object *effect,
				int diff_x, int diff_y);
void		init_monster_pos(t_data *data, int x, int y);
void		init_monster(t_data *data);
void		init_anim(t_data *data, t_animation *anim, int size, char *path);
void		put_interact_ui(t_data *data, t_object *obj);
void		show_monster(t_data *data, int i, int i2);
void		monster_move(t_data *data);
void		move_monster_to(t_data *data, int x, int y);
int			monster_should_move(t_data *data);
void		get_new_coords(t_data *data, int new_coord[2]);
void		continue_monster_anim(t_data *data, t_monster *monster);
void		get_to_player(t_data *data, int new_coord[2]);
int			can_see_player(t_data *data);
int			last_seen_x_y(t_data *data, int x, int y);
void		kill_player(t_data *data);
void		continue_death(t_data *data);
void		show_death(t_data *data);
void		get_good_facing(t_data *data, int x, int see_p);
int			get_monster_distance(t_data *data);
void		init_player_pos(t_data *data, int x, int y);
void		init_exit_pos(t_data *data, int x, int y);
int			window_manager(int event, void *param);
void		init_ui_to_null(t_data *data);
void		destroy_heart_anim(t_data *data);
void		continue_heart_anim(t_data *data);
void		free_menus(t_data *data);
void		start_game(t_data *data, int param);
void		quit_game(t_data *data, int param);
void		empty_func(t_data *data, int param);
void		init_menus(t_data *data);
void		show_current_menu(t_data *data);
void		fill_map(t_data *data, char *map);
void		go_to_option(t_data *data, int param);
void		go_to_main_menu(t_data *data, int param);
int			init_lumin_light(t_data *data, int index);
void		create_objects(t_data *data, char *img, int ind, int size);
void		show_parameters(t_data *data);
void		init_player(t_data *data);
void		change_luminosity(t_data *data, int param);
void		change_light(t_data *data, int param);
void		empty_loop(t_data *data);
void		put_lumin_light(t_data *data, int just_lumin);
void		change_resolution(t_data *data, int param);
void		save(t_data *data);
void		load_save(t_data *data);
void		switch_touhou(t_data *data, int param);
void		create_button(t_button *button, char *name, char *selected,
				void (*press)(t_data *data, int param));
void		go_to_extras(t_data *data, int param);
void		extras_menu_loop(t_data *data);
void		destroy_tex(t_data *data);
void		destroy_anim(t_data *data);
void		free_animations(t_data *data);
void		free_textures(t_data *data);
void		switch_debug(t_data *data, int param);
void		switch_old_tex(t_data *data, int param);
void		check_old_tex(t_data *data);
void		load_old_tex(t_data *data);
void		remove_all_flags(t_data *data);
void		init_editor_tab(t_data *data);
void		editor_place(t_data *data);
void		editor_remove_hide(t_data *data);
void		editor_place_hide(t_data *data);
void		editor_place_exit(t_data *data);
void		editor_place_item(t_data *data);
void		editor_remove_item(t_data *data);
void		editor_place_ground(t_data *data);
void		show_player_default_pos(t_data *data, int i, int i2);
void		show_editor_text(t_data *data);
int			is_finishable(t_data *data, int player_x, int player_y);
void		save_custom_map(t_data *data);
void		load_old_wall(t_data *data);
void		check_fnaf(t_data *data);
void		switch_fnaf(t_data *data, int param);
void		init_flags_anim(t_data *data);
void		continue_flag_anim(t_data *data);
void		continue_music(t_data *data);
void		stop_music(t_data *data);
void		play_music(t_data *data, char *music, int duration);
void		play_sound(char *sound);
void		check_car(t_data *data);
void		switch_car(t_data *data, int param);
void		load_car(t_data *data);
void		car_move(t_data *data);
void		stop_car(t_data *data);
int			get_car_speed(t_data *data);
void		create_new_explosion(t_data *data, int x, int y);
void		destroy_explosion(t_data *data);
void		destroy_car(t_data *data);
void		check_wall_car(t_data *data, int x, int y);
void		continue_all_effects(t_data *data);
void		show_explosion(t_data *data, int i, int i2);

#endif
