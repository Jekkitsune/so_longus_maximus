/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags_7.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 18:09:16 by fparis            #+#    #+#             */
/*   Updated: 2024/03/20 20:49:29 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	load_old_wall(t_data *data)
{
	int	i;

	i = tex_i(data, "ground_01");
	mlx_destroy_image(data->mlx, data->objects[i].texture);
	data->objects[i].texture = mlx_png_file_to_image(data->mlx,
			"tex/dev_tex/ground1.png", &data->objects[i].size_x,
			&data->objects[i].size_y);
	i = tex_i(data, "wall_01");
	mlx_destroy_image(data->mlx, data->objects[i].texture);
	data->objects[i].texture = mlx_png_file_to_image(data->mlx,
			"tex/dev_tex/wall1.png", &data->objects[i].size_x,
			&data->objects[i].size_y);
	i = tex_i(data, "wall_02");
	mlx_destroy_image(data->mlx, data->objects[i].texture);
	data->objects[i].texture = mlx_png_file_to_image(data->mlx,
			"tex/dev_tex/wall2.png", &data->objects[i].size_x,
			&data->objects[i].size_y);
}

void	init_purple_guy(t_data *data, t_animation *anim, int size)
{
	int	i;

	anim->tab = malloc(size * sizeof(void *));
	if (!anim->tab)
		free_exit(data, "could not load purple guy anim");
	anim->size = size;
	i = 0;
	while (i < size)
	{
		anim->tab[i] = NULL;
		i++;
	}
	anim->name = "purple_guy";
	anim->interval = 6;
	anim->index = 0;
	anim->clock = anim->interval;
	anim->tab[0] = mlx_png_file_to_image(data->mlx,
			"sprites/fnaf/purple/frame_0001.png", NULL, NULL);
}

void	init_flags_anim(t_data *data)
{
	if (data->flags.touhou)
		init_bad_apple(data,
			&data->player.anim[data->player.nb_anim - 1], 1020);
	else if (data->flags.fnaf)
	{
		init_purple_guy(data,
			&data->player.anim[data->player.nb_anim - 2], 91);
		init_anim(data, &data->player.anim[data->player.nb_anim - 1],
			13, "sprites/fnaf/jumpscare/foxy_jump_01.png");
		data->player.anim[data->player.nb_anim - 1].name = "foxy_jumpscare";
		data->player.anim[data->player.nb_anim - 1].interval = 4;
		data->player.anim[data->player.nb_anim - 1].index = 0;
	}
}

void	continue_flag_anim(t_data *data)
{
	t_animation	*current;

	current = data->player.current_anim;
	if (data->flags.touhou)
		continue_long_anim(data, current, "sprites/ba/frame_0001.png");
	else if (data->flags.fnaf)
		continue_long_anim(data, current, "sprites/fnaf/purple/frame_0001.png");
}
