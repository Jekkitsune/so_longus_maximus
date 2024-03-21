/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buttons_functions_5.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 18:17:54 by fparis            #+#    #+#             */
/*   Updated: 2024/03/20 17:37:12 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	check_old_tex(t_data *data)
{
	if (data->flags.old_tex)
	{
		data->menu_list[2].tab[1].name = "Old Textures [y]";
		data->menu_list[2].tab[1].selected_name = ">Old Textures [y]";
	}
	else
	{
		data->menu_list[2].tab[1].name = "Old Textures [n]";
		data->menu_list[2].tab[1].selected_name = ">Old Textures [n]";
	}
}

void	check_fnaf(t_data *data)
{
	if (data->flags.fnaf)
	{
		data->menu_list[2].tab[2].name = "Fnaf [y]";
		data->menu_list[2].tab[2].selected_name = ">Fnaf [y]";
	}
	else
	{
		data->menu_list[2].tab[2].name = "Fnaf [n]";
		data->menu_list[2].tab[2].selected_name = ">Fnaf [n]";
	}
}

void	switch_fnaf(t_data *data, int param)
{
	if (param == -1)
		return ;
	if (data->flags.fnaf)
		data->flags.fnaf = 0;
	else
	{
		remove_all_flags(data);
		data->flags.fnaf = 1;
	}
}
