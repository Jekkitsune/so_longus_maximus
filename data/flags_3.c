/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 22:14:54 by fparis            #+#    #+#             */
/*   Updated: 2024/03/19 18:12:31 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	init_items_tab_without_exit_program(t_data *data)
{
	int	i;

	data->item_collected = 0;
	data->items = malloc(sizeof(t_item) * data->nb_items);
	if (!data->items)
		return ;
	i = 0;
	while (i < data->nb_items)
	{
		data->items[i].object = get_tex(data, "black");
		data->items[i].collected = 0;
		i++;
	}
}

void	realloc_items(t_data *data, int add)
{
	int		last_size;
	int		i;
	t_item	*last_tab;

	last_size = data->nb_items;
	data->nb_items += add;
	last_tab = data->items;
	init_items_tab_without_exit_program(data);
	i = 0;
	while (last_tab && data->items && i < last_size)
	{
		if (ft_strcmp(last_tab[i].object->name, "black") != 0)
			add_item(data, last_tab[i].x, last_tab[i].y);
		i++;
	}
	free(last_tab);
}

void	editor_place_item(t_data *data)
{
	if (has_item(data, data->player.x, data->player.y) != NULL)
		return ;
	editor_place_ground(data);
	if (is_type(data, data->player.x, data->player.y, GROUND))
	{
		realloc_items(data, 1);
		add_item(data, data->player.x, data->player.y);
	}
}

void	editor_remove_item(t_data *data)
{
	t_item	*item;

	item = has_item(data, data->player.x, data->player.y);
	if (item)
	{
		item->object = get_tex(data, "black");
		realloc_items(data, -1);
	}
}

void	show_player_default_pos(t_data *data, int i, int i2)
{
	int			x;
	int			y;

	if (data->player.x + i == data->flags.editor_p_x
		&& data->player.y + i2 == data->flags.editor_p_y)
	{
		x = (data->win_x / 2) - (data->player.size_x / 2
				+ get_diff_env(data, 1)) + (data->tex_size * i);
		y = (data->win_y / 2) - (data->player.size_y - 20
				+ get_diff_env(data, 0)) + (data->tex_size * i2);
		mlx_put_image_to_window(data->mlx, data->win,
			data->player.default_sprite, x, y);
	}
}
