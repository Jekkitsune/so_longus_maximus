/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buttons_functions_4.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 16:16:21 by fparis            #+#    #+#             */
/*   Updated: 2024/03/27 19:46:00 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	check_touhou(t_data *data)
{
	if (data->flags.touhou)
	{
		data->menu_list[2].tab[0].name = "Touhou [y]";
		data->menu_list[2].tab[0].selected_name = ">Touhou [y]";
	}
	else
	{
		data->menu_list[2].tab[0].name = "Touhou [n]";
		data->menu_list[2].tab[0].selected_name = ">Touhou [n]";
	}
}

void	check_debug(t_data *data)
{
	if (data->flags.debug_mode)
	{
		data->menu_list[2].tab[3].name = "Map editor [y]";
		data->menu_list[2].tab[3].selected_name = ">Map editor [y]";
	}
	else
	{
		data->menu_list[2].tab[3].name = "Map editor [n]";
		data->menu_list[2].tab[3].selected_name = ">Map editor [n]";
	}
}

void	switch_old_tex(t_data *data, int param)
{
	if (param == -1)
		return ;
	play_sound("sounds/menu_press.wav");
	if (data->flags.old_tex)
		data->flags.old_tex = 0;
	else
	{
		remove_all_flags(data);
		data->flags.old_tex = 1;
	}
}

void	switch_debug(t_data *data, int param)
{
	if (param == -1)
		return ;
	play_sound("sounds/menu_press.wav");
	if (data->flags.debug_mode)
		data->flags.debug_mode = 0;
	else
	{
		remove_all_flags(data);
		data->flags.debug_mode = 1;
	}
}

void	extras_menu_loop(t_data *data)
{
	check_touhou(data);
	check_debug(data);
	check_old_tex(data);
	check_fnaf(data);
	check_car(data);
}
