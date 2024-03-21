/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monster_move.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 18:24:24 by fparis            #+#    #+#             */
/*   Updated: 2024/03/08 21:18:09 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	monster_move_second_half(t_data *data, int x, int y)
{
	if (x != 0 && data->monster.center_x * -x >= 0)
		data->monster.center_x += data->monster.speed * x;
	if (y != 0 && data->monster.center_y * -y >= 0)
		data->monster.center_y += data->monster.speed * y;
	if ((x == 0 || data->monster.center_x * -x <= 0)
		&& (y == 0 || data->monster.center_y * -y <= 0))
	{
		data->monster.last_pos[0] = data->monster.new_pos[0];
		data->monster.last_pos[1] = data->monster.new_pos[1];
	}
}

void	monster_move_first_half(t_data *data, int x, int y)
{
	if (x != 0 && data->monster.center_x * x < data->tex_size / 2)
		data->monster.center_x += data->monster.speed * x;
	if (y != 0 && data->monster.center_y * y < data->tex_size / 2)
		data->monster.center_y += data->monster.speed * y;
	if ((x == 0 || data->monster.center_x * x >= data->tex_size / 2)
		&& (y == 0 || data->monster.center_y * y >= data->tex_size / 2))
	{
		data->monster.x += x;
		data->monster.y += y;
		if (last_seen_x_y(data, data->monster.x, data->monster.y))
		{
			data->monster.last_seen_x = -1;
			data->monster.last_seen_y = -1;
		}
		if (x != 0)
			data->monster.center_x = ((data->monster.center_x * -x)
					+ (((data->monster.center_x * x)
							- (data->tex_size / 2)) * x)) * x;
		if (y != 0)
			data->monster.center_y = ((data->monster.center_y * -y)
					+ (((data->monster.center_y * y)
							- (data->tex_size / 2)) * y)) * y;
	}
}

void	monster_move_one(t_data *data, int x, int y)
{
	if (!monster_should_move(data))
	{
		data->monster.new_pos[0] = data->monster.x + x;
		data->monster.new_pos[1] = data->monster.y + y;
	}
	if (data->monster.x != data->monster.new_pos[0]
		|| data->monster.y != data->monster.new_pos[1])
		monster_move_first_half(data, data->monster.new_pos[0]
			- data->monster.last_pos[0],
			data->monster.new_pos[1] - data->monster.last_pos[1]);
	else
		monster_move_second_half(data, data->monster.new_pos[0]
			- data->monster.last_pos[0],
			data->monster.new_pos[1] - data->monster.last_pos[1]);
}

void	monster_move(t_data *data)
{
	int	new_coord[2];
	int	see_player;

	new_coord[0] = data->monster.new_pos[0] - data->monster.last_pos[0];
	new_coord[1] = data->monster.new_pos[1] - data->monster.last_pos[1];
	see_player = can_see_player(data);
	if (see_player && !data->flags.debug_mode && data->monster.x
		== data->player.x && data->monster.y == data->player.y)
		kill_player(data);
	if (monster_should_move(data))
		monster_move_one(data, new_coord[0], new_coord[1]);
	else
	{
		if (see_player || !last_seen_x_y(data, -1, -1))
		{
			get_to_player(data, new_coord);
			if (new_coord[0] == 0 && new_coord[1] == 0)
				get_new_coords(data, new_coord);
		}
		else
			get_new_coords(data, new_coord);
		move_monster_to(data, new_coord[0], new_coord[1]);
		get_good_facing(data, new_coord[0], see_player);
	}
}

void	move_monster_to(t_data *data, int x, int y)
{
	if (x >= -1 && x <= 1 && y >= -1 && y <= 1
		&& data->monster.last_pos[0] == data->monster.new_pos[0]
		&& data->monster.last_pos[1] == data->monster.new_pos[1]
		&& is_type(data, data->monster.x + x, data->monster.y + y, GROUND))
	{
		if (y < 0)
			data->monster.direction = 0;
		else if (x < 0)
			data->monster.direction = 1;
		else if (y > 0)
			data->monster.direction = 2;
		else if (x > 0)
			data->monster.direction = 3;
		monster_move_one(data, x, y);
	}
}
