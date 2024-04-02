/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 22:23:29 by fparis            #+#    #+#             */
/*   Updated: 2024/04/01 14:08:30 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	show_current_menu(t_data *data)
{
	int		i;
	int		space;
	int		color;
	char	*name;
	t_menu	*menu;

	mlx_clear_window(data->mlx, data->win);
	menu = data->current_menu;
	menu->menu_loop(data);
	i = 0;
	space = (data->win_y - menu->margin) / menu->size - 25;
	while (i < menu->size)
	{
		name = menu->tab[i].name;
		color = 0xFFFFFFFF;
		if (i == menu->button_index)
		{
			name = menu->tab[i].selected_name;
			color = 0xFFFFFF00;
		}
		mlx_string_put(data->mlx, data->win, data->win_x / 2
			- (ft_strlen(menu->tab[i].name) * 10 / 2),
			menu->margin + (i * space), color, name);
		i++;
	}
}

void	create_main_menu(t_data *data)
{
	data->menu_list[0].name = "main_menu";
	data->menu_list[0].size = 4;
	data->menu_list[0].button_index = 0;
	data->menu_list[0].tab = malloc(data->menu_list[0].size * sizeof(t_button));
	if (!data->menu_list[0].tab)
		free_exit(data, "could not allocate main menu");
	data->menu_list[0].menu_loop = main_menu_loop;
	data->menu_list[0].margin = 200;
	create_button(&data->menu_list[0].tab[0], "Select level", ">Select level",
		go_to_level_selection);
	create_button(&data->menu_list[0].tab[1], "Extras", ">Extras",
		go_to_extras);
	create_button(&data->menu_list[0].tab[2], "Options", ">Options",
		go_to_option);
	create_button(&data->menu_list[0].tab[3], "Quit", ">Quit", quit_game);
	data->current_menu = &data->menu_list[0];
}

void	create_option_menu(t_data *data)
{
	data->menu_list[1].name = "option";
	data->menu_list[1].size = 4;
	data->menu_list[1].button_index = 0;
	data->menu_list[1].tab = malloc(data->menu_list[1].size * sizeof(t_button));
	if (!data->menu_list[1].tab)
		free_exit(data, "could not allocate option menu");
	data->menu_list[1].menu_loop = show_parameters;
	data->menu_list[1].margin = 400;
	create_button(&data->menu_list[1].tab[0],
		"Change luminosity", "<- Change luminosity ->", change_luminosity);
	create_button(&data->menu_list[1].tab[1],
		"Change light UI", "<- Change light UI ->", change_light);
	create_button(&data->menu_list[1].tab[2],
		"Fullscreen", ">Fullscreen", change_resolution);
	create_button(&data->menu_list[1].tab[3],
		"Back", ">Back", go_to_main_menu);
}

void	create_extras_menu(t_data *data)
{
	data->menu_list[2].name = "extras";
	data->menu_list[2].size = 6;
	data->menu_list[2].button_index = 0;
	data->menu_list[2].tab = malloc(data->menu_list[2].size * sizeof(t_button));
	if (!data->menu_list[2].tab)
		free_exit(data, "could not allocate extras menu");
	data->menu_list[2].menu_loop = extras_menu_loop;
	data->menu_list[2].margin = 200;
	create_button(&data->menu_list[2].tab[0], "Touhou", ">Touhou",
		switch_touhou);
	create_button(&data->menu_list[2].tab[1], "Old Textures", ">Old Textures",
		switch_old_tex);
	create_button(&data->menu_list[2].tab[2], "Fnaf", ">Fnaf", switch_fnaf);
	create_button(&data->menu_list[2].tab[3], "Map editor", ">Map editor",
		switch_debug);
	create_button(&data->menu_list[2].tab[4], "Car", ">Car", switch_car);
	create_button(&data->menu_list[2].tab[5], "Back", ">Back", go_to_main_menu);
}

void	init_menus(t_data *data)
{
	data->nb_menu = 4;
	data->menu_list = malloc(data->nb_menu * sizeof(t_menu));
	if (!data->menu_list)
		free_exit(data, "could not allocate menus");
	create_main_menu(data);
	create_option_menu(data);
	create_extras_menu(data);
	create_level_selection(data);
}
