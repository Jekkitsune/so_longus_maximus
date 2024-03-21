/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anim_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 22:30:31 by fparis            #+#    #+#             */
/*   Updated: 2024/03/21 20:04:52 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	continue_player_anim(t_data *data)
{
	t_animation	*current;

	if (data->flags.debug_mode)
		return ;
	if (data->player.dead)
		return (continue_death(data));
	current = data->player.current_anim;
	current->clock--;
	if (data->flags.bad_apple_launched || data->flags.fnaf)
		return (continue_flag_anim(data));
	if (current->clock < 0)
	{
		current->index++;
		if (current->index >= current->size)
		{
			if (is_idle(data, current->name))
			{
				change_random_idle(data);
				current = data->player.current_anim;
			}
			current->index = 0;
		}
		current->clock = current->interval;
	}
	data->player.sprite = current->tab[current->index];
}

void	continue_monster_anim(t_data *data, t_monster *monster)
{
	t_animation	*current;

	if (!data->monster.exist || data->flags.fnaf)
		return ;
	current = &monster->anim[0];
	current->clock--;
	if (current->clock < 0)
	{
		current->index++;
		if (current->index >= current->size)
			current->index = 0;
		current->clock = current->interval;
	}
	monster->sprite = monster->anim[monster->facing].tab[current->index];
}

int	get_anim_index(t_data *data, char *name)
{
	int	i;

	i = 0;
	while (i < data->player.nb_anim)
	{
		if (ft_strcmp(name, data->player.anim[i].name) == 0)
			return (i);
		i++;
	}
	return (10);
}

void	change_anim(t_data *data, char *name, int reset)
{
	int	index;

	if (data->player.current_anim && (data->flags.bad_apple_launched
		|| data->flags.old_tex || data->flags.debug_mode
		|| (data->flags.fnaf && !data->player.dead)))
		return ;
	index = get_anim_index(data, name);
	data->player.current_anim = &data->player.anim[index];
	if (reset)
	{
		data->player.current_anim->index = 0;
		data->player.current_anim->clock = data->player.current_anim->interval;
	}
}

char	*get_random_anim(t_animation *tab, int start, int end)
{
	int	size;
	int	i;

	size = end - start + 1;
	if (size < 0)
		return (NULL);
	i = rand() % size;
	i += start;
	return (tab[i].name);
}
