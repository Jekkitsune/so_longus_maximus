/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chunk_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 17:44:14 by fparis            #+#    #+#             */
/*   Updated: 2024/03/25 00:47:42 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

t_object	*check_exit(t_data *data, int x, int y)
{
	if (x == data->exit_x && y == data->exit_y)
	{
		if (data->exit_y - 1 >= 0
			&& data->map[data->exit_x][data->exit_y - 1]->type == WALL)
			return (get_tex(data, "exit_01"));
		else
			return (get_tex(data, "exit_02"));
	}
	return (NULL);
}

t_object	*check_interactible(t_data *data, int x, int y)
{
	t_item		*item;
	t_hideout	*hideout;
	t_object	*obj;

	obj = NULL;
	if (x < 0 || x >= data->size_x || y < 0 || y >= data->size_y)
		return (NULL);
	item = has_item(data, x, y);
	if (item)
		return (item->object);
	hideout = has_hideout(data, x, y);
	if (hideout)
		return (hideout->object);
	obj = check_exit(data, x, y);
	return (obj);
}

int	get_diff_env(t_data *data, int want_x)
{
	if (want_x)
	{
		if (data->player.x == 1)
			return (100);
		if (data->player.x == data->size_x - 2)
			return (-100);
		if (data->player.hidden)
			return (0);
		else
			return (data->center_x);
	}
	if (data->player.y == 1)
		return (100);
	if (data->player.y == data->size_y - 2)
		return (-100);
	if (data->player.hidden)
		return (-40);
	return (data->center_y);
}

void	show_interactible(t_data *data, int i, int i2)
{
	t_object	*obj;
	int			diff_x;
	int			diff_y;

	obj = check_interactible(data, data->player.x + i, data->player.y + i2);
	if (obj)
	{
		diff_x = obj->size_x / 2 + get_diff_env(data, 1);
		diff_y = obj->size_y / 2 + get_diff_env(data, 0);
		if (obj->type == HIDE)
			diff_y -= 50 - data->tex_size;
		if (ft_strcmp(obj->name, "exit_01") == 0)
			diff_y += data->tex_size;
		mlx_put_image_to_window(data->mlx, data->win, obj->texture,
			(data->win_x / 2 - diff_x) + (data->tex_size * i),
			(data->win_y / 2 - diff_y) + (data->tex_size * i2));
	}
	if (i == 0 && i2 == 0)
		put_interact_ui(data, obj);
	show_monster(data, i, i2);
	if (data->flags.debug_mode)
		show_player_default_pos(data, i, i2);
}

void	show_obj(t_data *data, int i, int i2)
{
	int			diff_x;
	int			diff_y;
	int			middle;

	middle = data->chunk_size / 2;
	diff_x = data->tex_size / 2 + get_diff_env(data, 1);
	diff_y = data->tex_size / 2 + get_diff_env(data, 0);
	if (data->chunk[middle + i][middle + i2] == NULL)
		mlx_put_image_to_window(data->mlx, data->win, data->void_tex,
			(data->win_x / 2 - diff_x) + (data->tex_size * i),
			(data->win_y / 2 - diff_y) + (data->tex_size * i2));
	else
		mlx_put_image_to_window(data->mlx, data->win,
			data->chunk[middle + i][middle + i2]->texture,
			(data->win_x / 2 - diff_x) + (data->tex_size * i),
			(data->win_y / 2 - diff_y) + (data->tex_size * i2));
}
