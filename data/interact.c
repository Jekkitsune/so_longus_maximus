/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interact.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 20:49:49 by fparis            #+#    #+#             */
/*   Updated: 2024/03/27 19:39:39 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	interact(t_data *data)
{
	t_item		*item;
	t_hideout	*hideout;

	if (data->player.x == data->exit_x && data->player.y == data->exit_y)
	{
		if (data->item_collected >= data->nb_items)
			mlx_loop_end(data->mlx);
		else
			put_text(data, get_tex(data, "number_01"), 30, 120);
	}
	else
	{
		item = has_item(data, data->player.x, data->player.y);
		if (item)
		{
			item->collected = 1;
			data->item_collected++;
			put_text(data, get_tex(data, "number_01"), 30, 120);
			play_sound("sounds/item_collected.wav");
			return ;
		}
		hideout = has_hideout(data, data->player.x, data->player.y);
		if (hideout)
			hide(data);
	}
}

void	put_interact_ui(t_data *data, t_object *obj)
{
	if (!data->player.hidden && (obj || (data->player.x == data->exit_x
				&& data->player.y == data->exit_y)) && !data->flags.debug_mode)
		data->player.can_interact = 1;
	else
		data->player.can_interact = 0;
}
