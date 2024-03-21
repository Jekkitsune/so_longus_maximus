/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monster_move_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 19:29:03 by fparis            #+#    #+#             */
/*   Updated: 2024/03/19 18:17:12 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	monster_should_move(t_data *data)
{
	return (data->monster.last_pos[0] != data->monster.new_pos[0]
		|| data->monster.last_pos[1] != data->monster.new_pos[1]);
}

void	add_good_coord(int new_coord[2], int coord)
{
	if (coord == 0)
		new_coord[1] -= 1;
	else if (coord == 1)
		new_coord[0] -= 1;
	else if (coord == 2)
		new_coord[1] += 1;
	else if (coord == 3)
		new_coord[0] += 1;
}

void	get_new_coords(t_data *data, int new_coord[2])
{
	int	test[4];
	int	random;
	int	curr_direc;

	curr_direc = data->monster.direction;
	test[0] = is_type(data, data->monster.x, data->monster.y - 1, GROUND);
	test[1] = is_type(data, data->monster.x - 1, data->monster.y, GROUND);
	test[2] = is_type(data, data->monster.x, data->monster.y + 1, GROUND);
	test[3] = is_type(data, data->monster.x + 1, data->monster.y, GROUND);
	if (test[curr_direc] && rand() % 5 != 4)
		add_good_coord(new_coord, curr_direc);
	else
	{
		random = rand() % 2;
		if (random == 0)
			random = 3;
		if (test[(curr_direc + random) % 4])
			add_good_coord(new_coord, (curr_direc + random) % 4);
		else if (test[(curr_direc + random + 2) % 4])
			add_good_coord(new_coord, (curr_direc + random + 2) % 4);
		else if (test[curr_direc])
			add_good_coord(new_coord, curr_direc);
		else
			add_good_coord(new_coord, (curr_direc + 2) % 4);
	}
}

void	get_good_facing(t_data *data, int x, int see_player)
{
	if (!see_player || x != 0)
	{
		if (x > 0)
			data->monster.facing = 0;
		else if (x < 0)
			data->monster.facing = 1;
		return ;
	}
	if (data->monster.x == data->player.x)
	{
		if (data->center_x > 0)
			data->monster.facing = 0;
		else
			data->monster.facing = 1;
		return ;
	}
	else if (data->monster.x < data->player.x)
		data->monster.facing = 0;
	else
		data->monster.facing = 1;
}

int	get_monster_distance(t_data *data)
{
	double	res;

	if (!data->monster.exist)
		return (100);
	res = sqrt(pow((double)(data->monster.x - data->player.x), 2)
			+ pow((double)(data->monster.y - data->player.y), 2));
	return ((int)res);
}
