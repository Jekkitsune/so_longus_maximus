/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 18:40:02 by fparis            #+#    #+#             */
/*   Updated: 2024/02/29 12:47:43 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	get_type(t_data *data, int x, int y)
{
	if (x < 0 || y < 0 || x >= data->size_x || y >= data->size_y)
		return (1);
	return (data->map[x][y]->type == WALL);
}

int	*get_adjacent(t_data *data, int x, int y, int res[9])
{
	res[0] = get_type(data, x - 1, y -1);
	res[1] = get_type(data, x, y - 1);
	res[2] = get_type(data, x + 1, y - 1);
	res[3] = get_type(data, x - 1, y);
	res[4] = get_type(data, x, y);
	res[5] = get_type(data, x + 1, y);
	res[6] = get_type(data, x - 1, y + 1);
	res[7] = get_type(data, x, y + 1);
	res[8] = get_type(data, x + 1, y + 1);
	return (res);
}

t_object	*get_more_wall(t_data *data, int adj[9])
{
	if (!adj[3] && !adj[5] && adj[1] && adj[7])
		return (get_tex(data, "wall_07"));
	if (!adj[8] && adj[7] && adj[5])
		return (get_tex(data, "corner_04"));
	if (!adj[6] && adj[7] && adj[3])
		return (get_tex(data, "corner_05"));
	if (!adj[3] && !adj[7] && adj[5] && adj[1])
		return (get_tex(data, "corner_01"));
	if (!adj[5] && !adj[7] && adj[3] && adj[1])
		return (get_tex(data, "corner_02"));
	if (!adj[3] && adj[1] && adj[7])
		return (get_tex(data, "wall_05"));
	if (!adj[5] && adj[1] && adj[7])
		return (get_tex(data, "wall_06"));
	if (!adj[1] && !adj[3] && !adj[5] && !adj[7])
		return (get_tex(data, "wall_08"));
	if (!adj[7])
		return (get_tex(data, get_random_tex(data->objects,
					tex_i(data, "wall_01"), tex_i(data, "wall_04"))));
	return (get_tex(data, "black"));
}

t_object	*get_wall(t_data *data, int x, int y)
{
	int	adj[9];

	get_adjacent(data, x, y, adj);
	if (!adj[1] && !adj[3] && !adj[5] && adj[7])
		return (get_tex(data, "corner_11"));
	if (!adj[8] && adj[1] && !adj[3] && adj[7] && adj[5])
		return (get_tex(data, "corner_08"));
	if (!adj[6] && adj[1] && !adj[5] && adj[7] && adj[3])
		return (get_tex(data, "corner_07"));
	if (!adj[8] && !adj[1] && !adj[3] && adj[7])
		return (get_tex(data, "corner_12"));
	if (!adj[6] && !adj[1] && !adj[5] && adj[7])
		return (get_tex(data, "corner_13"));
	if (!adj[3] && !adj[5] && !adj[7] && adj[1])
		return (get_tex(data, "corner_03"));
	if (!adj[6] && !adj[8] && adj[7] && adj[3] && adj[5])
		return (get_tex(data, "corner_06"));
	if (!adj[3] && !adj[1] && adj[7] && adj[5])
		return (get_tex(data, "corner_09"));
	if (!adj[5] && !adj[1] && adj[7] && adj[3])
		return (get_tex(data, "corner_10"));
	return (get_more_wall(data, adj));
}
