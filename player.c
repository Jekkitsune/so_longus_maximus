/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 21:30:03 by fparis            #+#    #+#             */
/*   Updated: 2024/03/24 21:08:00 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	stun_player(t_data *data, int time)
{
	data->player.can_move = 0;
	data->player.stun_timer = time;
	data->player.speed = 0;
}

void	move(t_data *data)
{
	if (data->player.movement[0] || data->player.movement[1]
		|| data->player.movement[2] || data->player.movement[3] > 0)
	{
		data->player.speed = data->player.base_speed
			+ (data->player.base_speed * data->player.is_running);
		if (data->player.hidden)
			hide(data);
	}
	else
		data->player.speed = 0;
	if (data->player.speed != 0)
	{
		move_anim(data);
		if (data->player.movement[0])
			move_chunk(data, 0, -data->player.speed);
		if (data->player.movement[1])
			move_chunk(data, -data->player.speed, 0);
		if (data->player.movement[2])
			move_chunk(data, 0, data->player.speed);
		if (data->player.movement[3])
			move_chunk(data, data->player.speed, 0);
	}
	else
		idle_anim(data);
}

void	player_loop(t_data *data)
{
	if (data->player.stun_timer >= 0)
		data->player.stun_timer--;
	if (data->player.stun_timer == 0)
		data->player.can_move = 1;
	if (data->player.is_running && data->player.speed > 0
		&& !data->flags.debug_mode)
		data->player.stamina -= 2;
	else if (data->player.speed > 0)
		data->player.stamina++;
	else
		data->player.stamina += 2;
	if (data->player.stamina >= data->player.max_stamina)
		data->player.stamina = data->player.max_stamina;
	if (data->player.stamina < 0)
	{
		stun_player(data, 140);
		if (data->player.direction == 1)
			change_anim(data, "idle_r1", 1);
		else
			change_anim(data, "idle_l1", 1);
	}
	if (data->player.can_move && !data->flags.car)
		move(data);
	else if (data->player.can_move && data->flags.car)
		car_move(data);
}

int	get_diff_player(t_data *data, int want_x)
{
	if (want_x)
	{
		if (data->player.x == 1)
			return (data->center_x - 100);
		if (data->player.x == data->size_x - 2)
			return (data->center_x + 100);
		else
			return (0);
	}
	if (data->player.y == 1)
		return (data->center_y - 100);
	if (data->player.y == data->size_y - 2)
		return (data->center_y + 100);
	else
		return (0);
}

void	show_player(t_data *data)
{
	int	p_x;
	int	p_y;

	if (data->player.dead)
		return (show_death(data));
	p_x = data->win_x / 2 - data->player.size_x / 2 + get_diff_player(data, 1);
	p_y = data->win_y / 2 - (data->player.size_y - 20) + (30 * data->flags.car)
		+ get_diff_player(data, 0);
	if (!data->player.hidden)
	{
		if (!data->flags.debug_mode && !data->flags.car)
		{
			mlx_put_image_to_window(data->mlx, data->win,
				data->ui.shadow.texture, data->win_x / 2
				- data->ui.shadow.size_x / 2 + get_diff_player(data, 1),
				data->win_y / 2 + 10 - data->ui.shadow.size_y / 2
				+ get_diff_player(data, 0));
		}
		mlx_put_image_to_window(data->mlx, data->win,
			data->player.sprite, p_x, p_y);
	}
}
