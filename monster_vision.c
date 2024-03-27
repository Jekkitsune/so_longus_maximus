/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monster_vision.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 20:03:02 by fparis            #+#    #+#             */
/*   Updated: 2024/03/27 20:11:34 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	monster_raycast(t_data *data)
{
	int	x;
	int	y;

	x = data->monster.x;
	y = data->monster.y;
	while (x != data->player.x && y != data->player.y)
	{
		if (x > data->player.x)
			x--;
		else if (x < data->player.x)
			x++;
		if (y > data->player.y)
			y--;
		else if (y < data->player.y)
			y++;
		if (!is_type(data, x, y, GROUND))
			return (0);
	}
	return (1);
}

int	can_see_player(t_data *data)
{
	if (data->monster.on_screen && data->player.hidden_fr == 0
		&& monster_raycast(data))
	{
		data->monster.last_seen_x = data->player.x;
		data->monster.last_seen_y = data->player.y;
		if (data->monster.scream_timer <= 0)
		{
			data->monster.scream_timer = 60 * 30;
			if (data->flags.fnaf)
			{
				if (rand() % 2)
					play_sound("sounds/fnaf/CAPNFOXY.wav");
				else
					play_sound("sounds/fnaf/FoxyHereICome.wav");
			}
			else
				play_sound("sounds/monster/monster_aggro.wav");
		}
		return (1);
	}
	return (0);
}

int	last_seen_x_y(t_data *data, int x, int y)
{
	return (data->monster.last_seen_x == x && data->monster.last_seen_y == y);
}
