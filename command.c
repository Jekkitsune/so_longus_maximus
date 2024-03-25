/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 15:56:53 by fparis            #+#    #+#             */
/*   Updated: 2024/03/24 18:44:27 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	menu_command(t_data *data, int key)
{
	t_menu	*menu;

	menu = data->current_menu;
	if ((key == 26 || key == 82) && menu->button_index > 0)
		menu->button_index--;
	if ((key == 22 || key == 81) && menu->button_index < menu->size - 1)
		menu->button_index++;
	if (key == 40 || key == 79 || key == 7)
		menu->tab[menu->button_index].press(data, 1);
	if (key == 4 || key == 80)
		menu->tab[menu->button_index].press(data, -1);
}

int	window_manager(int event, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (event == 0)
		mlx_loop_end(data->mlx);
	return (0);
}

void	register_player_movement(t_data *data, int key, int pressed)
{
	if (key == 26)
		data->player.movement[0] = pressed;
	if (key == 4)
		data->player.movement[1] = pressed;
	if (key == 22)
		data->player.movement[2] = pressed;
	if (key == 7)
		data->player.movement[3] = pressed;
	if ((key == 7 && pressed) || (key == 4 && !pressed
			&& data->player.movement[3]))
		data->player.direction = 1;
	if ((key == 4 && pressed) || (key == 7 && !pressed
			&& data->player.movement[1]))
		data->player.direction = 0;
}

int	key_down_manager(int key, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (key == 41)
		mlx_loop_end(data->mlx);
	if (data->current_menu)
	{
		menu_command(data, key);
		return (0);
	}
	if (key == 26 || key == 4 || key == 22 || key == 7)
		register_player_movement(data, key, 1);
	else if (key == 8 && data->player.can_interact)
		interact(data);
	else if (key == 5 && data->flags.touhou)
		bad_apple_manager(data);
	else if (key == 225)
		data->player.is_running = 1;
	if (data->flags.debug_mode)
		debug_command(data, key);
	return (0);
}

int	key_up_manager(int key, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (data->current_menu)
		return (0);
	if (key == 26 || key == 4 || key == 22 || key == 7)
		register_player_movement(data, key, 0);
	if (key == 225)
		data->player.is_running = 0;
	return (0);
}
