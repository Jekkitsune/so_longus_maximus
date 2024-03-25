/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 16:49:14 by fparis            #+#    #+#             */
/*   Updated: 2024/03/24 23:48:32 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	check_corner_up(t_data *data, int direc_y)
{
	int	x;
	int	y;

	x = data->player.x;
	y = data->player.y + direc_y;
	if ((is_type(data, x + 1, y, WALL)
			&& data->center_x + data->player.hitbox_x > (data->tex_size / 2))
		|| (is_type(data, x - 1, y, WALL)
			&& data->center_x - data->player.hitbox_x < -(data->tex_size / 2)))
		return (0);
	return (1);
}

int	check_corner(t_data *data, int direc, int direc_y)
{
	int	x;
	int	y;

	if (data->flags.car)
		return (1);
	x = data->player.x;
	y = data->player.y;
	if (direc != 0)
	{
		x = x + direc;
		if ((is_type(data, x, y + 1, WALL)
				&& data->center_y
				+ data->player.hitbox_y > (data->tex_size / 2))
			|| (is_type(data, x, y - 1, WALL)
				&& data->center_y
				- data->player.hitbox_y < -(data->tex_size / 2)))
			return (0);
	}
	else if (direc_y != 0)
		return (check_corner_up(data, direc_y));
	return (1);
}

void	check_wall_side(t_data *data, int *x)
{
	if (*x > 0 && is_type(data, data->player.x + 1, data->player.y, WALL))
	{
		if (*x + data->player.hitbox_x >= (data->tex_size / 2)
			- data->center_x)
			*x = ((data->tex_size / 2) - data->center_x
					- data->player.hitbox_x);
	}
	if (*x > 0
		&& *x + data->player.hitbox_x + data->center_x >= (data->tex_size / 2)
		&& !check_corner(data, 1, 0))
		*x = 0;
	if (*x < 0 && is_type(data, data->player.x - 1, data->player.y, WALL))
	{
		if (*x - data->player.hitbox_x <= -(data->tex_size / 2)
			- data->center_x)
			*x = (-(data->tex_size / 2) - data->center_x
					+ data->player.hitbox_x);
	}
	if (*x < 0
		&& *x - data->player.hitbox_x + data->center_x <= -(data->tex_size / 2)
		&& !check_corner(data, -1, 0))
		*x = 0;
}

void	check_wall_up(t_data *data, int *y)
{
	if (*y > 0 && is_type(data, data->player.x, data->player.y + 1, WALL))
	{
		if (*y + data->player.hitbox_y >= (data->tex_size / 2)
			- data->center_y)
			*y = ((data->tex_size / 2) - data->center_y
					- data->player.hitbox_y) * check_corner(data, 0, 1);
	}
	if (*y > 0
		&& *y + data->player.hitbox_y + data->center_y >= (data->tex_size / 2)
		&& !check_corner(data, 0, 1))
		*y = 0;
	if (*y < 0 && is_type(data, data->player.x, data->player.y - 1, WALL))
	{
		if (*y - data->player.hitbox_y <= -(data->tex_size / 2)
			- data->center_y)
			*y = -(data->tex_size / 2) - data->center_y
				+ data->player.hitbox_y * check_corner(data, 0, 1);
	}
	if (*y < 0
		&& *y - data->player.hitbox_y + data->center_y <= -(data->tex_size / 2)
		&& !check_corner(data, 0, -1))
		*y = 0;
}

void	check_wall(t_data *data, int *x, int *y)
{
	int	last_x;
	int	last_y;

	if (data->player.x >= data->size_x || data->player.x < 0
		|| data->player.y >= data->size_y || data->player.y < 0)
		return ;
	last_x = *x;
	last_y = *y;
	if (data->flags.car)
		check_wall_car(data, *x, *y);
	check_wall_side(data, x);
	check_wall_up(data, y);
	hideout_collision(data, x, y);
	if (data->flags.car && (last_x != *x || last_y != *y))
		stop_car(data);
}
