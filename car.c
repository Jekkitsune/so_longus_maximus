/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   car.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 18:23:09 by fparis            #+#    #+#             */
/*   Updated: 2024/03/25 01:26:40 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	load_car(t_data *data)
{
	int	i;
	
	if (!data->flags.car)
		return ;
	i = get_anim_index(data, "default_r");
	mlx_destroy_image(data->mlx, data->player.anim[i].tab[0]);
	data->player.anim[i].tab[0] = mlx_png_file_to_image(data->mlx,
			"sprites/car/car_r.png", &data->player.size_x,
			&data->player.size_y);
	i = get_anim_index(data, "default_l");
	mlx_destroy_image(data->mlx, data->player.anim[i].tab[0]);
	data->player.anim[i].tab[0] = mlx_png_file_to_image(data->mlx,
			"sprites/car/car_l.png", &data->player.size_x,
			&data->player.size_y);
	data->flags.car_tab[0] = 0;
	data->flags.car_tab[1] = 0;
	data->flags.car_delay[0] = 15;
	data->flags.car_delay[1] = 15;
	data->flags.nb_explosion = 0;
	data->flags.explosion_list = NULL;
	init_anim(data, &data->flags.explosion_anim, 30,
		"sprites/car/explosion/frame_01.png");
	data->flags.explosion_anim.name = "explosion";
	data->flags.explosion_anim.interval = 3;
}

void	change_speed(t_data *data, int direc, int value, int change_speed)
{
	if (data->flags.car_delay[direc] > 0)
		data->flags.car_delay[direc] -= change_speed;
	else
	{
		data->flags.car_delay[direc] = 15;
		data->flags.car_tab[direc] += value;
	}
}

void	bring_to_zero(t_data *data, int direc)
{
	if (data->flags.car_tab[direc] < 0)
		change_speed(data, direc, 1, 15);
	else if (data->flags.car_tab[direc] > 0)
		change_speed(data, direc, -1, 15);
}

void	car_change_state(t_data *data)
{
	if (data->player.movement[0] || data->player.movement[1]
		|| data->player.movement[2] || data->player.movement[3] > 0)
	{
		if (data->player.hidden)
			hide(data);
	}
	if (data->player.direction == 1)
		data->player.current_anim =
			&data->player.anim[get_anim_index(data, "default_r")];
	else if (data->player.direction == 0)
		data->player.current_anim =
			&data->player.anim[get_anim_index(data, "default_l")];
}

void	car_move(t_data *data)
{
	int	speed_cap;

	speed_cap = 30;
	car_change_state(data);
	if (data->player.movement[0] && data->flags.car_tab[0] < speed_cap)
		change_speed(data, 0, 1, 3 + (15 * (data->flags.car_tab[0] < 0)));
	else if (data->player.movement[2] && data->flags.car_tab[0] > -speed_cap)
		change_speed(data, 0, -1, 3 + (15 * (data->flags.car_tab[0] > 0)));
	else if (!data->player.movement[0] && !data->player.movement[2])
		bring_to_zero(data, 0);
	if (data->player.movement[1] && data->flags.car_tab[1] < speed_cap)
		change_speed(data, 1, 1, 3 + (15 * (data->flags.car_tab[1] < 0)));
	else if (data->player.movement[3] && data->flags.car_tab[1] > -speed_cap)
		change_speed(data, 1, -1, 3 + (15 * (data->flags.car_tab[1] > 0)));
	else if (!data->player.movement[1] && !data->player.movement[3])
		bring_to_zero(data, 1);
	move_chunk(data, -data->flags.car_tab[1], -data->flags.car_tab[0]);
}
