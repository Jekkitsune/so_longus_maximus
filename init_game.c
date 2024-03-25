/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 00:55:53 by fparis            #+#    #+#             */
/*   Updated: 2024/03/25 01:04:34 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	init_player(t_data *data)
{
	data->player.base_speed = 3 + (data->flags.debug_mode * 10);
	data->player.speed = 0;
	data->player.can_move = 1;
	data->player.is_running = 0;
	data->player.direction = 1;
	data->player.movement[0] = 0;
	data->player.movement[1] = 0;
	data->player.movement[2] = 0;
	data->player.movement[3] = 0;
	data->player.max_stamina = 1400;
	data->player.hidden = 0;
	data->player.hidden_fr = 0;
	data->player.stamina = data->player.max_stamina;
	data->player.sprite = data->player.default_sprite;
	data->player.hitbox_x = data->player.size_x / 4;
	data->player.hitbox_y = data->player.size_y / 6;
	data->player.dead = 0;
	data->player.current_anim = NULL;
	if (data->flags.fnaf)
		change_anim(data, "purple_guy", 1);
	else
		change_anim(data, "default_r", 1);
}

void	init_game(t_data *data)
{
	init_player(data);
	data->center_x = 0;
	data->center_y = 0;
	init_chunk_tab(data);
	show_chunk(data);
	if (data->flags.debug_mode)
	{
		data->flags.editor_p_x = data->player.x;
		data->flags.editor_p_y = data->player.y;
	}
	if (data->flags.fnaf)
		play_music(data, "sounds/fnaf/The-man-behind-the-slaughter.wav",
			201 * 60);
	if (data->flags.car)
		play_music(data, "sounds/car/Evangelion.wav", 230 * 60);
}

void	init_player_pos(t_data *data, int x, int y)
{
	if (data->player.x != -1 || data->player.y != -1)
	{
		data->player.x = -2;
		data->player.y = -2;
	}
	else
	{
		data->player.x = x;
		data->player.y = y;
	}
	data->map[x][y] = get_object(data, GROUND);
}

void	init_exit_pos(t_data *data, int x, int y)
{
	if (data->exit_x != -1 || data->exit_y != -1)
	{
		data->exit_x = -2;
		data->exit_y = -2;
	}
	else
	{
		data->exit_x = x;
		data->exit_y = y;
	}
	data->map[x][y] = get_object(data, GROUND);
}
