/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   car_3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 23:20:39 by fparis            #+#    #+#             */
/*   Updated: 2024/03/27 22:56:36 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	explode_wall(t_data *data, int x, int y)
{
	data->map[x][y] = get_object(data, GROUND);
	create_new_explosion(data, x, y);
	play_sound("sounds/car/explosion.wav");
}

t_effect	*has_explosion(t_data *data, int x, int y)
{
	int	i;

	i = 0;
	if (!data->flags.explosion_list)
		return (NULL);
	while (i < data->flags.nb_explosion)
	{
		if (data->flags.explosion_list[i].x == x
			&& data->flags.explosion_list[i].y == y)
			return (&data->flags.explosion_list[i]);
		i++;
	}
	return (NULL);
}

void	show_explosion(t_data *data, int i, int i2)
{
	int			x;
	int			y;
	t_effect	*effect;

	if (!data->flags.car)
		return ;
	effect = has_explosion(data, data->player.x + i, data->player.y + i2);
	if (effect)
	{
		x = (data->win_x / 2) - (100 + get_diff_env(data, 1))
			+ (data->tex_size * i);
		y = (data->win_y / 2) - (100 + get_diff_env(data, 0))
			+ (data->tex_size * i2);
		mlx_put_image_to_window(data->mlx, data->win, effect->sprite, x, y);
	}
}

void	check_wall_car(t_data *data, int x, int y)
{
	if (get_car_speed(data) >= 20)
	{
		if (y > 0 && is_type(data, data->player.x, data->player.y + 1, WALL)
			&& y + data->player.hitbox_y >= ((data->tex_size / 2)
				- data->center_y))
			explode_wall(data, data->player.x, data->player.y + 1);
		if (y < 0 && is_type(data, data->player.x, data->player.y - 1, WALL)
			&& y - data->player.hitbox_y <= (-(data->tex_size / 2)
				- data->center_y))
			explode_wall(data, data->player.x, data->player.y - 1);
		if (x > 0 && is_type(data, data->player.x + 1, data->player.y, WALL)
			&& x + data->player.hitbox_x >= ((data->tex_size / 2)
				- data->center_x))
			explode_wall(data, data->player.x + 1, data->player.y);
		if (x < 0 && is_type(data, data->player.x - 1, data->player.y, WALL)
			&& x - data->player.hitbox_x <= (-(data->tex_size / 2)
				- data->center_x))
			explode_wall(data, data->player.x - 1, data->player.y);
	}
}
