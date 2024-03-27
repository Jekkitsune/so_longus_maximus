/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_anim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 17:54:04 by fparis            #+#    #+#             */
/*   Updated: 2024/03/27 22:56:52 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	is_idle(t_data *data, char *anim)
{
	if (data->player.direction == 1)
	{
		if (ft_strcmp(anim, "idle_r1") == 0
			|| ft_strcmp(anim, "idle_r2") == 0
			|| ft_strcmp(anim, "idle_r3") == 0
			|| ft_strcmp(anim, "default_r") == 0)
			return (1);
		else
			return (0);
	}
	else if (data->player.direction == 0)
	{
		if (ft_strcmp(anim, "idle_l1") == 0
			|| ft_strcmp(anim, "idle_l2") == 0
			|| ft_strcmp(anim, "idle_l3") == 0
			|| ft_strcmp(anim, "default_l") == 0)
			return (1);
		else
			return (0);
	}
	return (0);
}

void	idle_anim(t_data *data)
{
	if (data->player.current_anim
		&& is_idle(data, data->player.current_anim->name) == 0)
	{
		if (data->player.direction == 1)
			change_anim(data, "default_r", 1);
		else if (data->player.direction == 0)
			change_anim(data, "default_l", 1);
	}
}

void	move_anim(t_data *data)
{
	if (data->player.is_running && data->player.speed != 0)
	{
		if (data->player.direction == 1
			&& ft_strcmp(data->player.current_anim->name, "run_r") != 0)
			change_anim(data, "run_r", 1);
		else if (data->player.direction == 0
			&& ft_strcmp(data->player.current_anim->name, "run_l") != 0)
			change_anim(data, "run_l", 1);
	}
	else if (data->player.speed != 0)
	{
		if (data->player.direction == 1
			&& ft_strcmp(data->player.current_anim->name, "walk_r") != 0)
			change_anim(data, "walk_r", 1);
		else if (data->player.direction == 0
			&& ft_strcmp(data->player.current_anim->name, "walk_l") != 0)
			change_anim(data, "walk_l", 1);
	}
}

void	change_random_idle(t_data *data)
{
	char	*current;

	current = data->player.current_anim->name;
	if (ft_strcmp(current, "default_r") == 0)
		change_anim(data, get_random_anim(data->player.anim, 0, 2), 1);
	else if (ft_strcmp(current, "default_l") == 0)
		change_anim(data, get_random_anim(data->player.anim, 3, 5), 1);
	else if (is_idle(data, current))
	{
		if (data->player.direction == 1)
			change_anim(data, "default_r", 1);
		else if (data->player.direction == 0)
			change_anim(data, "default_l", 1);
	}
}
