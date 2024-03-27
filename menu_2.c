/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 22:03:42 by fparis            #+#    #+#             */
/*   Updated: 2024/03/27 22:43:30 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	create_level_selection(t_data *data)
{
	data->menu_list[3].name = "level selection";
	data->menu_list[3].size = 3;
	data->menu_list[3].button_index = 0;
	data->menu_list[3].tab = malloc(data->menu_list[3].size * sizeof(t_button));
	if (!data->menu_list[3].tab)
		free_exit(data, "could not allocate levels menu");
	data->menu_list[3].menu_loop = level_selection_loop;
	data->menu_list[3].margin = 200;
	create_button(&data->menu_list[3].tab[0], "Start", ">Start", start_game);
	create_button(&data->menu_list[3].tab[1], "Change level:", ">Change level:",
		change_level_selected);
	create_button(&data->menu_list[3].tab[2], "Back", ">Back",
		go_to_main_menu);
}
