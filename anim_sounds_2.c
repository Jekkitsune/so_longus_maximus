/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anim_sounds_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 19:30:46 by fparis            #+#    #+#             */
/*   Updated: 2024/03/27 22:58:59 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	breathing(int index, int clock)
{
	if (index == 0 && clock == 1)
		play_sound("sounds/player/breathing.wav");
}

//	if (index == 10 && clock == 30)
//		play_sound("sounds/heart_stop.wav");
void	death_sound(int index, int clock)
{
	if (index < 11 && clock % 10 == 0)
		play_sound("sounds/heart_01.wav");
	else if (index < 11 && clock % 10 == 2)
		play_sound("sounds/heart_02.wav");
	if (index == 10 && clock == 25)
		play_sound("sounds/death.wav");
}
