/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buttons_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 22:43:17 by fparis            #+#    #+#             */
/*   Updated: 2024/03/27 19:45:26 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	empty_func(t_data *data, int param)
{
	if (data || param)
		return ;
}

void	start_game(t_data *data, int param)
{
	char	*map;

	if (param < 0)
		return ;
	play_sound("sounds/menu_press.wav");
	if (data->flags.touhou || data->flags.fnaf)
	{
		destroy_anim(data);
		free_animations(data);
		init_player_anim(data);
	}
	load_old_tex(data);
	load_car(data);
	map = data->map_name;
	init_map(data, map);
	init_items_tab(data);
	init_hideouts_tab(data);
	fill_map(data, map);
	is_correct_map(data);
	init_monster(data);
	init_textures(data);
	init_game(data);
	data->current_menu = NULL;
}

void	go_to_option(t_data *data, int param)
{
	if (param < 0)
		return ;
	play_sound("sounds/menu_press.wav");
	data->current_menu = &data->menu_list[1];
	data->current_menu->button_index = 0;
}

void	go_to_main_menu(t_data *data, int param)
{
	if (param < 0)
		return ;
	play_sound("sounds/menu_press.wav");
	if (data->current_menu == &data->menu_list[1])
		save(data);
	data->current_menu = &data->menu_list[0];
	data->current_menu->button_index = 0;
}

void	quit_game(t_data *data, int param)
{
	if (param < 0)
		return ;
	play_sound("sounds/menu_press.wav");
	mlx_loop_end(data->mlx);
}
