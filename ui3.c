/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui3.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 18:51:50 by fparis            #+#    #+#             */
/*   Updated: 2024/03/19 18:12:09 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	show_light_anim(t_data *data)
{
	if (data->ui.is_dark > 0)
	{
		data->ui.is_dark--;
		screen_effect(data, &data->ui.dark, 0, 0);
	}
	else
	{
		if (data->ui.light_timer > 0)
			data->ui.light_timer--;
		else if (data->ui.in_anim > 0)
		{
			data->ui.in_anim--;
			data->ui.is_dark = rand() % 20 + 3;
			data->ui.light_timer = rand() % 5 + 5;
		}
		else
		{
			data->ui.in_anim = rand() % 3 + 1;
			data->ui.is_dark = 20;
			data->ui.light_timer = rand() % 3000 + 1000;
		}
	}
}

void	init_ui_to_null(t_data *data)
{
	data->ui.dark.texture = NULL;
	data->ui.shadow.texture = NULL;
	data->ui.big_shadow.texture = NULL;
	data->ui.interact.texture = NULL;
	data->ui.hide_ui.texture = NULL;
	data->ui.light = NULL;
	data->ui.luminosity = NULL;
	data->ui.red.texture = NULL;
	data->ui.heart_anim.tab = NULL;
}

void	continue_heart_anim(t_data *data)
{
	int			distance;
	t_animation	*current;

	distance = get_monster_distance(data) - 4;
	distance = ft_min(distance, 100);
	distance = ft_max(distance, 2);
	current = &data->ui.heart_anim;
	current->clock++;
	if (((current->index == 0 || distance < current->interval)
			&& current->clock > distance) || (current->index != 0
			&& current->clock > current->interval))
	{
		current->index++;
		if (current->index >= current->size
			- (distance < current->interval * 2))
			current->index = 0;
		current->clock = 0;
	}
	mlx_put_image_to_window(data->mlx, data->win, current->tab[current->index],
		data->win_x - data->win_x / 10, data->win_y / 30);
}

int	init_lumin_light(t_data *data, int index)
{
	int	i;

	i = index;
	create_objects(data, "UI/Udark_01.png", i, 3);
	while (i < index + 3)
	{
		data->objects[i].type = 'U';
		i++;
	}
	create_objects(data, "UI/Ulight_effect_01.png", i, 8);
	while (i < index + 11)
	{
		data->objects[i].type = 'U';
		i++;
	}
	return (i);
}

void	put_lumin_light(t_data *data, int just_lumin)
{
	if (!data->show_env)
		return ;
	if (data->ui.luminosity)
		screen_effect(data, data->ui.luminosity, 0, 0);
	if (data->ui.light && !just_lumin)
		screen_effect(data, data->ui.light, get_diff_player(data, 1),
			get_diff_player(data, 0) - data->player.size_y / 4);
}
