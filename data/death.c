/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 18:10:08 by fparis            #+#    #+#             */
/*   Updated: 2024/03/27 20:56:13 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	kill_player(t_data *data)
{
	if (data->flags.bad_apple_launched)
		data->flags.bad_apple_launched = 0;
	stun_player(data, -1);
	data->player.dead = 1;
	if (data->player.hidden)
		play_sound("sounds/door_exit.wav");
	data->player.hidden = 0;
	data->ui.hide = 1;
	if (data->flags.fnaf)
	{
		change_anim(data, "foxy_jumpscare", 1);
		stop_music(data);
		play_sound("sounds/fnaf/jumpscare.wav");
	}
	else
	{
		if (data->monster.exist && data->monster.facing == 1)
			change_anim(data, "death_r", 1);
		else
			change_anim(data, "death_l", 1);
	}
	data->monster.exist = 0;
}

int	close_to_wall(t_data *data)
{
	if ((data->monster.facing
			& is_type(data, data->player.x + 1, data->player.y, WALL))
		|| (!data->monster.facing
			&& is_type(data, data->player.x - 1, data->player.y, WALL)))
		return (0);
	return (100 - (data->monster.facing * 200));
}

void	show_death(t_data *data)
{
	int	p_x;
	int	p_y;
	int	s_x;
	int	s_y;

	if (data->flags.fnaf)
	{
		mlx_put_image_to_window(data->mlx, data->win,
			data->player.sprite, data->win_x / 2 - 320, data->win_y / 2 - 180);
		return ;
	}
	p_x = data->win_x / 2 - 300 / 2 + get_diff_player(data, 1)
		- close_to_wall(data);
	p_y = data->win_y / 2 - (275 - 20) + get_diff_player(data, 0);
	s_x = data->win_x / 2 - data->ui.big_shadow.size_x / 2
		+ get_diff_player(data, 1) - close_to_wall(data);
	s_y = data->win_y / 2 + 10 - data->ui.big_shadow.size_y / 2
		+ get_diff_player(data, 0);
	if (data->show_env)
		mlx_put_image_to_window(data->mlx, data->win,
			data->ui.big_shadow.texture, s_x, s_y);
	mlx_put_image_to_window(data->mlx, data->win,
		data->player.sprite, p_x, p_y);
}

void	paint_red(t_data *data)
{
	data->show_env = 0;
	screen_effect(data, &data->ui.red, 0, 0);
	show_player(data);
}

void	continue_death(t_data *data)
{
	t_animation	*current;
	int			fnaf;

	fnaf = data->flags.fnaf;
	current = data->player.current_anim;
	current->clock--;
	if (current->clock < 0)
	{
		current->index++;
		if (current->index >= current->size)
		{
			mlx_loop_end(data->mlx);
			return ;
		}
		current->clock = current->interval;
		if (current->index == 6 && !fnaf)
			current->clock = 40;
		if ((current->index == 10 || current->index == 16) && !fnaf)
			current->clock = 80;
		if (current->index == 15 && !fnaf)
			current->clock = 20;
	}
	if (current->index >= 11 && !fnaf)
		paint_red(data);
	data->player.sprite = current->tab[current->index];
}
