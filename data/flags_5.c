/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags_5.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 23:11:40 by fparis            #+#    #+#             */
/*   Updated: 2024/03/19 17:57:07 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	editor_place_ground(t_data *data)
{
	if (data->player.x == data->monster.x && data->player.y == data->monster.y)
	{
		data->monster.x = -1;
		data->monster.y = -1;
	}
	if (data->player.x == data->flags.editor_p_x
		&& data->player.y == data->flags.editor_p_y)
	{
		data->flags.editor_p_x = -1;
		data->flags.editor_p_y = -1;
	}
	if (data->player.x == data->exit_x && data->player.y == data->exit_y)
	{
		data->exit_x = -1;
		data->exit_y = -1;
	}
	if (has_hideout(data, data->player.x, data->player.y) != NULL)
		editor_remove_hide(data);
	if (has_item(data, data->player.x, data->player.y) != NULL)
		editor_remove_item(data);
	if (is_type(data, data->player.x, data->player.y, WALL))
		data->map[data->player.x][data->player.y] = get_object(data, GROUND);
}

void	editor_place_wall(t_data *data)
{
	if (is_type(data, data->player.x, data->player.y, WALL))
		return ;
	editor_place_ground(data);
	if (is_type(data, data->player.x, data->player.y, GROUND))
		data->map[data->player.x][data->player.y] = get_object(data, WALL);
}

void	editor_place_player(t_data *data)
{
	if (data->player.x == data->flags.editor_p_x
		&& data->player.y == data->flags.editor_p_y)
		return ;
	editor_place_ground(data);
	data->flags.editor_p_x = data->player.x;
	data->flags.editor_p_y = data->player.y;
}

void	editor_place_monster(t_data *data)
{
	if (data->player.x == data->monster.x
		&& data->player.y == data->monster.y)
		return ;
	editor_place_ground(data);
	data->monster.x = data->player.x;
	data->monster.y = data->player.y;
}

void	editor_place(t_data *data)
{
	char	chara;

	if (data->player.x == 0 || data->player.x == data->size_x - 1
		|| data->player.y == 0 || data->player.y == data->size_y - 1)
		return ;
	chara = data->flags.editor_tab[data->flags.editor_index];
	if (chara == GROUND)
		editor_place_ground(data);
	if (chara == WALL)
		editor_place_wall(data);
	if (chara == ITEM)
		editor_place_item(data);
	if (chara == HIDE)
		editor_place_hide(data);
	if (chara == EXIT)
		editor_place_exit(data);
	if (chara == PLAYER)
		editor_place_player(data);
	if (chara == MONSTER)
		editor_place_monster(data);
	init_textures(data);
	load_chunk(data, 0, 0);
	data->flags.editor_saved = 0;
}
