/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   car_4.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 00:05:04 by fparis            #+#    #+#             */
/*   Updated: 2024/03/28 18:49:24 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	continue_effect_anim(t_data *data, t_effect *effect)
{
	if (effect->clock > 0)
		effect->clock--;
	else
	{
		effect->clock = effect->anim->interval;
		effect->anim_index++;
		if (effect->anim_index >= effect->anim->size - 1)
		{
			destroy_explosion(data);
			return ;
		}
	}
	effect->sprite = effect->anim->tab[effect->anim_index];
}

void	continue_all_effects(t_data *data)
{
	int	i;

	i = 0;
	while (data->flags.explosion_list && i < data->flags.nb_explosion)
	{
		continue_effect_anim(data, &data->flags.explosion_list[i]);
		i++;
	}
}
