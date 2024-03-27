/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monster.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 17:48:30 by fparis            #+#    #+#             */
/*   Updated: 2024/03/27 19:54:48 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	init_monster_pos(t_data *data, int x, int y)
{
	int	random;

	random = rand() % 2;
	if (data->monster.x == -1 || random)
	{
		data->monster.x = x;
		data->monster.y = y;
	}
	data->map[x][y] = get_object(data, GROUND);
}

void	show_monster(t_data *data, int i, int i2)
{
	int			x;
	int			y;

	if (!data->monster.exist)
		return ;
	if (data->player.x + i == data->monster.x
		&& data->player.y + i2 == data->monster.y)
	{
		x = (data->win_x / 2) - (data->monster.size_x / 2
				+ get_diff_env(data, 1)
				- data->monster.center_x) + (data->tex_size * i);
		y = (data->win_y / 2) - (data->monster.size_y - 20
				+ get_diff_env(data, 0)
				- data->monster.center_y) + (data->tex_size * i2);
		mlx_put_image_to_window(data->mlx, data->win,
			data->ui.big_shadow.texture,
			x - 10, y + data->monster.size_y - 40);
		mlx_put_image_to_window(data->mlx, data->win, data->monster.sprite,
			x, y);
		data->monster.on_screen = 1;
	}
}

void	init_monster_anim(t_data *data)
{
	init_anim(data, &data->monster.anim[0], 8,
		"sprites/monster/monster_run_r_01.png");
	init_anim(data, &data->monster.anim[1], 8,
		"sprites/monster/monster_run_l_01.png");
	data->monster.anim[0].name = "run_r";
	data->monster.anim[0].interval = 10;
	data->monster.anim[0].clock = data->monster.anim[0].interval;
	data->monster.anim[0].index = 0;
	data->monster.anim[1].name = "run_l";
	data->monster.anim[1].interval = 10;
	data->monster.anim[1].clock = data->monster.anim[1].interval;
	data->monster.anim[1].index = 0;
	if (data->flags.fnaf)
		data->monster.default_sprite = mlx_png_file_to_image(data->mlx,
				"sprites/fnaf/foxy.png",
				&data->monster.size_x, &data->monster.size_y);
	else
		data->monster.default_sprite = mlx_png_file_to_image(data->mlx,
				"sprites/monster/monster_run_r_01.png",
				&data->monster.size_x, &data->monster.size_y);
	data->monster.sprite = data->monster.default_sprite;
	data->monster.scream_timer = 0;
}

void	init_monster(t_data *data)
{
	if (data->monster.x != -1 || data->flags.debug_mode)
	{
		data->monster.exist = 1;
		data->monster.nb_anim = 2;
		data->monster.anim
			= malloc(data->monster.nb_anim * sizeof(t_animation));
		if (!data->monster.anim)
			free_exit(data, "could not load monster");
		init_monster_anim(data);
		data->monster.center_x = 0;
		data->monster.center_y = 0;
		data->monster.base_speed = 5;
		data->monster.speed = data->monster.base_speed;
		data->monster.facing = 0;
		data->monster.direction = rand() % 4;
		data->monster.new_pos[0] = data->monster.x;
		data->monster.new_pos[1] = data->monster.y;
		data->monster.last_pos[0] = data->monster.x;
		data->monster.last_pos[1] = data->monster.y;
		data->monster.follow_player = 0;
		data->monster.last_seen_x = -1;
		data->monster.last_seen_y = -1;
	}
	else
		data->monster.exist = 0;
}
