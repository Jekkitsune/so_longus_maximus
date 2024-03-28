/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buttons_functions_6.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 22:07:26 by fparis            #+#    #+#             */
/*   Updated: 2024/03/27 22:48:19 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	get_map_index(t_data *data, char *map)
{
	int	i;

	i = 0;
	while (data->all_maps[i] && map)
	{
		if (ft_strcmp(data->all_maps[i], map) == 0)
			return (i);
		i++;
	}
	return (i);
}

void	change_level_selected(t_data *data, int param)
{
	play_sound("sounds/menu_move.wav");
	data->map_name = data->all_maps[get_map_index(data, data->map_name)
		+ param];
	if (!data->map_name)
		data->map_name = data->all_maps[1];
	else if (ft_strcmp(data->map_name, data->all_maps[0]) == 0)
		data->map_name = data->all_maps[data->nb_maps - 1];
}

void	level_selection_loop(t_data *data)
{
	mlx_string_put(data->mlx, data->win, data->win_x / 2
		- (ft_strlen(data->map_name) * 10 / 2),
		200 + ((data->win_y - 200) / 3),
		0xFFFFFFFF, data->map_name);
}

void	go_to_level_selection(t_data *data, int param)
{
	if (param < 0)
		return ;
	play_sound("sounds/menu_press.wav");
	data->current_menu = &data->menu_list[3];
	data->current_menu->button_index = 0;
}
