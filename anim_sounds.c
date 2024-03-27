/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anim_sounds.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 17:35:17 by fparis            #+#    #+#             */
/*   Updated: 2024/03/27 21:08:03 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	p_walk_sound(int index, int clock)
{
	int		i;
	char	*path;

	if ((index == 1 || index == 8) && clock == 0)
	{
		path = malloc(ft_strlen("sounds/player/walk_01.wav") + 1);
		if (!path)
			return ;
		ft_strlcpy(path, "sounds/player/walk_01.wav",
			ft_strlen("sounds/player/walk_01.wav") + 1);
		i = (random() % 18) + 1;
		path[20] = '0' + (i % 10);
		path[19] = '0' + (i / 10);
		play_sound(path);
		free(path);
	}
}

void	p_run_sound(int index, int clock)
{
	int		i;
	char	*path;

	if ((index == 0 || index == 4) && clock == 0)
	{
		path = malloc(ft_strlen("sounds/player/walk_01.wav") + 1);
		if (!path)
			return ;
		ft_strlcpy(path, "sounds/player/walk_01.wav",
			ft_strlen("sounds/player/walk_01.wav") + 1);
		i = (random() % 18) + 1;
		path[20] = '0' + (i % 10);
		path[19] = '0' + (i / 10);
		play_sound(path);
		free(path);
	}
}

void	m_run_sound(int index, int clock)
{
	int		i;
	char	*path;

	if ((index == 0 || index == 4) && clock == 0)
	{
		path = malloc(ft_strlen("sounds/monster/walk_01.wav") + 1);
		if (!path)
			return ;
		ft_strlcpy(path, "sounds/monster/walk_01.wav",
			ft_strlen("sounds/monster/walk_01.wav") + 1);
		i = (random() % 18) + 1;
		path[21] = '0' + (i % 10);
		path[20] = '0' + (i / 10);
		play_sound(path);
		free(path);
	}
}

void	heart_sound(int index, int clock)
{
	if (clock != 0)
		return ;
	if (index == 2)
		play_sound("sounds/heart_01.wav");
	else if (index == 3)
		play_sound("sounds/heart_02.wav");
}

void	init_anim_sound(t_data *data)
{
	data->player.anim[get_anim_index(data, "walk_r")].anim_sound = p_walk_sound;
	data->player.anim[get_anim_index(data, "walk_l")].anim_sound = p_walk_sound;
	data->player.anim[get_anim_index(data, "run_r")].anim_sound = p_run_sound;
	data->player.anim[get_anim_index(data, "run_l")].anim_sound = p_run_sound;
	data->ui.heart_anim.anim_sound = heart_sound;
	if (data->monster.exist)
		data->monster.anim[0].anim_sound = m_run_sound;
	data->player.anim[get_anim_index(data, "idle_r1")].anim_sound = breathing;
	data->player.anim[get_anim_index(data, "idle_l1")].anim_sound = breathing;
	data->player.anim[get_anim_index(data, "death_r")].anim_sound = death_sound;
	data->player.anim[get_anim_index(data, "death_l")].anim_sound = death_sound;
}
