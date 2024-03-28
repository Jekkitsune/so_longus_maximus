/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   car_2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 21:30:07 by fparis            #+#    #+#             */
/*   Updated: 2024/03/25 00:44:30 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	stop_car(t_data *data)
{
	data->flags.car_tab[0] = 0;
	data->flags.car_tab[1] = 0;
	data->flags.car_delay[0] = 15;
	data->flags.car_delay[1] = 15;
}

int	get_car_speed(t_data *data)
{
	int	first;
	int	second;

	if (data->flags.car_tab[0] > 0)
		first = data->flags.car_tab[0];
	else
		first = -data->flags.car_tab[0];
	if (data->flags.car_tab[1] > 0)
		second = data->flags.car_tab[1];
	else
		second = -data->flags.car_tab[1];
	if (first > second)
		return (first);
	return (second);
}

void	cpy_effect(t_effect *effect_2, t_effect *effect_1)
{
	effect_2->x = effect_1->x;
	effect_2->y = effect_1->y;
	effect_2->anim = effect_1->anim;
	effect_2->anim_index = effect_1->anim_index;
	effect_2->clock = effect_1->clock;
	effect_2->sprite = effect_1->sprite;
}

void	create_new_explosion(t_data *data, int x, int y)
{
	t_effect	*new_list;
	int			i;

	data->flags.nb_explosion++;
	new_list = malloc(data->flags.nb_explosion * sizeof(t_effect));
	if (!new_list)
		free_exit(data, "Failed to alloc new explosion");
	i = 0;
	while (i < data->flags.nb_explosion - 1)
	{
		cpy_effect(&new_list[i], &data->flags.explosion_list[i]);
		i++;
	}
	new_list[i].x = x;
	new_list[i].y = y;
	new_list[i].anim = &data->flags.explosion_anim;
	new_list[i].anim_index = 0;
	new_list[i].clock = new_list[i].anim->interval;
	new_list[i].sprite = new_list[i].anim->tab[0];
	if (data->flags.explosion_list)
		free(data->flags.explosion_list);
	data->flags.explosion_list = new_list;
}

void	destroy_explosion(t_data *data)
{
	t_effect	*new_list;
	int			i;

	data->flags.nb_explosion--;
	if (data->flags.nb_explosion <= 0)
	{
		if (data->flags.explosion_list)
			free(data->flags.explosion_list);
		data->flags.explosion_list = NULL;
		return ;
	}
	new_list = malloc(data->flags.nb_explosion * sizeof(t_effect));
	if (!new_list)
		free_exit(data, "Failed to alloc new explosion");
	i = 1;
	while (i < data->flags.nb_explosion + 1)
	{
		cpy_effect(&new_list[i - 1], &data->flags.explosion_list[i]);
		i++;
	}
	if (data->flags.explosion_list)
		free(data->flags.explosion_list);
	data->flags.explosion_list = new_list;
}
