/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chunk.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 15:08:02 by fparis            #+#    #+#             */
/*   Updated: 2024/03/25 00:48:58 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	load_chunk(t_data *data, int x, int y)
{
	int	i;
	int	i2;
	int	new_x;
	int	new_y;

	data->player.x += x;
	data->player.y += y;
	new_x = data->player.x - data->chunk_size / 2;
	new_y = data->player.y - data->chunk_size / 2;
	i = 0;
	while (i < data->chunk_size)
	{
		i2 = 0;
		while (i2 < data->chunk_size)
		{
			if ((new_x + i) < 0 || (new_y + i2) < 0
				|| (new_x + i) >= data->size_x || (new_y + i2) >= data->size_y)
				data->chunk[i][i2] = NULL;
			else
				data->chunk[i][i2] = data->map[new_x + i][new_y + i2];
			i2++;
		}
		i++;
	}
	return ;
}

void	init_chunk_tab(t_data *data)
{
	int	i;

	data->chunk_size = (data->win_x / data->tex_size) + 2;
	if (data->chunk_size % 2 == 0)
		data->chunk_size++;
	data->chunk = malloc(data->chunk_size * sizeof(t_object *));
	if (!data->chunk)
		free_exit(data, "could not load chunk tab");
	i = 0;
	while (i < data->chunk_size)
	{
		data->chunk[i] = malloc(data->chunk_size * sizeof(t_object *));
		if (!data->chunk[i])
			free_exit(data, "could not load chunk tab");
		i++;
	}
	data->show_env = 1;
	load_chunk(data, 0, 0);
}

void	show_line(t_data *data, int start, int end,
void (*show)(t_data *data, int i, int i2))
{
	int	i;
	int	i2;

	i2 = start;
	while (i2 < end)
	{
		i = -data->chunk_size / 2;
		while (i < data->chunk_size / 2 + 1)
		{
			show(data, i, i2);
			i++;
		}
		i2++;
	}
}

void	show_chunk(t_data *data)
{
	if (data->monster.exist)
		data->monster.on_screen = 0;
	if (data->show_env)
	{
		mlx_clear_window(data->mlx, data->win);
		show_line(data, -data->chunk_size / 2,
			data->chunk_size / 2 + 1, show_obj);
		show_line(data, -data->chunk_size / 2, 1, show_interactible);
		show_player(data);
		show_line(data, 1, data->chunk_size / 2 + 1, show_interactible);
		if (data->flags.car)
			show_line(data, -data->chunk_size / 2,
				data->chunk_size / 2 + 1, show_explosion);
	}
}

void	move_chunk(t_data *data, int x, int y)
{
	if (!data->flags.debug_mode)
		check_wall(data, &x, &y);
	data->center_x += x;
	data->center_y += y;
	add_meters(data, x, y);
	check_chunk_load(data);
}
