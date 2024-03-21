/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buttons_functions_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 15:17:48 by fparis            #+#    #+#             */
/*   Updated: 2024/03/19 18:13:52 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	change_luminosity(t_data *data, int param)
{
	int	ind_lumin;

	if (!data->ui.luminosity)
	{
		if (param == 1)
			data->ui.luminosity = get_tex(data, "dark_01");
		else
			data->ui.luminosity = get_tex(data, "dark_03");
	}
	else
	{
		ind_lumin = tex_i(data, data->ui.luminosity->name) + param;
		if (ind_lumin > tex_i(data, "dark_03")
			|| ind_lumin < tex_i(data, "dark_01"))
			data->ui.luminosity = NULL;
		else
			data->ui.luminosity = &data->objects[ind_lumin];
	}
}

void	change_light(t_data *data, int param)
{
	int	ind_light;

	if (!data->ui.light)
	{
		if (param == 1)
			data->ui.light = get_tex(data, "light_effect_01");
		else
			data->ui.light = get_tex(data, "light_effect_08");
	}
	else
	{
		ind_light = tex_i(data, data->ui.light->name) + param;
		if (ind_light > tex_i(data, "light_effect_08")
			|| ind_light < tex_i(data, "light_effect_01"))
			data->ui.light = NULL;
		else
			data->ui.light = &data->objects[ind_light];
	}
}

void	place_background(t_data *data)
{
	int	i;
	int	i2;

	i = 0;
	while (i < data->win_x)
	{
		mlx_put_image_to_window(data->mlx, data->win,
			get_tex(data, "wall_01")->texture, i, 0);
		i += data->tex_size;
	}
	i = 0;
	while (i < data->win_x)
	{
		i2 = data->tex_size;
		while (i2 < data->win_y)
		{
			mlx_put_image_to_window(data->mlx, data->win,
				get_tex(data, "ground_01")->texture, i, i2);
			i2 += data->tex_size;
		}
		i += data->tex_size;
	}
}

void	place_player_template(t_data *data)
{
	int	y;

	y = data->tex_size / 2;
	mlx_put_image_to_window(data->mlx, data->win,
		data->ui.shadow.texture, data->win_x / 2
		- data->ui.shadow.size_x / 2,
		y + data->player.size_y - 30);
	mlx_put_image_to_window(data->mlx, data->win,
		data->player.sprite, data->win_x / 2 - data->player.size_x / 2, y);
}

void	show_parameters(t_data *data)
{
	place_background(data);
	continue_player_anim(data);
	place_player_template(data);
	if (data->ui.luminosity)
		screen_effect(data, data->ui.luminosity, 0, -data->tex_size / 2);
	if (data->ui.light)
	{
		if (data->win_x >= 1500)
			screen_effect(data, data->ui.light, 0, -data->tex_size * 2 + 70);
		else
			screen_effect(data, data->ui.light, 0, -data->tex_size / 2 - 30);
	}
	if (data->fullscreen == 1)
	{
		data->menu_list[1].tab[2].name = "Fullscreen [y]";
		data->menu_list[1].tab[2].selected_name = ">Fullscreen [y]";
	}
	else
	{
		data->menu_list[1].tab[2].name = "Fullscreen [n]";
		data->menu_list[1].tab[2].selected_name = ">Fullscreen [n]";
	}
}
