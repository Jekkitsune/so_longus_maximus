/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sounds_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 16:56:17 by fparis            #+#    #+#             */
/*   Updated: 2024/03/25 01:06:22 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	stop_music(t_data *data)
{
	data->music_duration = 0;
	if (data->current_music && data->music_pid)
		kill(data->music_pid, SIGKILL);
	data->current_music = NULL;
	data->music_pid = 0;
}

void	play_music(t_data *data, char *music, int duration)
{
	pid_t	pid;

	stop_music(data);
	pid = fork();
	if (pid == 0)
		execlp("paplay", "paplay", music, NULL);
	data->music_pid = pid;
	data->music_duration = duration;
	data->music_full_duration = duration;
	data->current_music = music;
}

void	continue_music(t_data *data)
{
	if (!data->current_music)
		return ;
	if (data->music_duration > 0)
		data->music_duration--;
	else
		play_music(data, data->current_music, data->music_full_duration);
}

void	play_sound(char *sound)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
		execlp("paplay", "paplay", sound, NULL);
}
