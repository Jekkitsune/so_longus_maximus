/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monster_move_3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 20:20:08 by fparis            #+#    #+#             */
/*   Updated: 2024/03/28 21:11:24 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	try_path(t_data *data, int x, int y, int len)
{
	int	test;
	int	res;

	len++;
	if (!is_type(data, x, y, GROUND) || len > 7)
		return (0);
	if (x == data->monster.last_seen_x && y == data->monster.last_seen_y)
		return (len);
	test = 0;
	res = 0;
	test = try_path(data, x - 1, y, len);
	if (test && (test <= res || !res))
		res = test;
	test = try_path(data, x + 1, y, len);
	if (test && (test <= res || !res))
		res = test;
	test = try_path(data, x, y - 1, len);
	if (test && (test <= res || !res))
		res = test;
	test = try_path(data, x + 1, y + 1, len);
	if (test && (test <= res || !res))
		res = test;
	return (res);
}

void	try_direc(t_data *data, int new_coord[2], int *res, int co[2])
{
	int	test;

	if (is_type(data, data->monster.x, data->monster.y + co[1], GROUND)
		&& is_type(data, data->monster.x + co[0], data->monster.y, GROUND))
	{
		test = try_path(data, data->monster.x + co[0],
				data->monster.y + co[1], 0);
		if (test && (test <= *res || !*res))
		{
			*res = test;
			new_coord[0] = co[0];
			new_coord[1] = co[1];
		}
	}
}

void	get_to_player(t_data *data, int new_coord[2])
{
	int	res;
	int	coords[2];

	res = 0;
	coords[0] = -1;
	while (coords[0] <= 1)
	{
		coords[1] = -1;
		while (coords[1] <= 1)
		{
			if (coords[0] != 0 || coords[1] != 0)
				try_direc(data, new_coord, &res, coords);
			coords[1]++;
		}
		coords[0]++;
	}
}

int	last_seen_x_y(t_data *data, int x, int y)
{
	return (data->monster.last_seen_x == x && data->monster.last_seen_y == y);
}
