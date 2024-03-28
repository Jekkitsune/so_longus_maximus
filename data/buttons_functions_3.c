/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buttons_functions_3.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 17:09:57 by fparis            #+#    #+#             */
/*   Updated: 2024/03/27 19:45:50 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	create_button(t_button *button, char *name, char *selected,
void (*press)(t_data *data, int param))
{
	button->name = name;
	button->selected_name = selected;
	button->press = press;
}

void	go_to_extras(t_data *data, int param)
{
	if (param < 0)
		return ;
	play_sound("sounds/menu_press.wav");
	data->current_menu = &data->menu_list[2];
	data->current_menu->button_index = 0;
}

void	empty_loop(t_data *data)
{
	if (data)
		return ;
}

void	change_resolution(t_data *data, int param)
{
	if (param == -1)
		return ;
	play_sound("sounds/menu_press.wav");
	if (data->fullscreen)
		data->fullscreen = 0;
	else
		data->fullscreen = 1;
}

void	switch_touhou(t_data *data, int param)
{
	if (param == -1)
		return ;
	play_sound("sounds/menu_press.wav");
	if (data->flags.touhou)
		data->flags.touhou = 0;
	else
	{
		remove_all_flags(data);
		data->flags.touhou = 1;
	}
}
