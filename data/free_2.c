/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 21:24:23 by fparis            #+#    #+#             */
/*   Updated: 2024/03/24 23:14:23 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	destroy_anim(t_data *data)
{
	int	i;
	int	i2;

	if (data->player.anim)
	{
		i = 0;
		while (i < data->player.nb_anim && data->player.anim[i].tab)
		{
			i2 = 0;
			while (i2 < data->player.anim[i].size)
			{
				if (data->player.anim[i].tab[i2])
					mlx_destroy_image(data->mlx, data->player.anim[i].tab[i2]);
				i2++;
			}
			i++;
		}
	}
	if (data->player.default_sprite)
		mlx_destroy_image(data->mlx, data->player.default_sprite);
	destroy_car(data);
}

void	destroy_monster(t_data *data)
{
	int	i;
	int	i2;

	if (data->monster.anim)
	{
		i = 0;
		while (i < data->monster.nb_anim && data->monster.anim[i].tab)
		{
			i2 = 0;
			while (i2 < data->monster.anim[i].size)
			{
				if (data->monster.anim[i].tab[i2])
					mlx_destroy_image(data->mlx, data->monster.anim[i].tab[i2]);
				i2++;
			}
			i++;
		}
	}
	if (data->monster.default_sprite)
		mlx_destroy_image(data->mlx, data->monster.default_sprite);
}

void	destroy_tex(t_data *data)
{
	int	i;

	if (data->objects)
	{
		i = 0;
		while (i < data->nb_objects)
		{
			if (data->objects[i].texture)
				mlx_destroy_image(data->mlx, data->objects[i].texture);
			i++;
		}
	}
}

void	destroy_ui(t_data *data)
{
	if (data->ui.dark.texture)
		mlx_destroy_image(data->mlx, data->ui.dark.texture);
	if (data->ui.shadow.texture)
		mlx_destroy_image(data->mlx, data->ui.shadow.texture);
	if (data->ui.big_shadow.texture)
		mlx_destroy_image(data->mlx, data->ui.big_shadow.texture);
	if (data->ui.interact.texture)
		mlx_destroy_image(data->mlx, data->ui.interact.texture);
	if (data->ui.hide_ui.texture)
		mlx_destroy_image(data->mlx, data->ui.hide_ui.texture);
	if (data->ui.red.texture)
		mlx_destroy_image(data->mlx, data->ui.red.texture);
	destroy_heart_anim(data);
}

void	destroy_all_img(t_data *data)
{
	destroy_anim(data);
	destroy_monster(data);
	destroy_tex(data);
	destroy_ui(data);
}
