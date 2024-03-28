/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_anim.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 16:56:36 by fparis            #+#    #+#             */
/*   Updated: 2024/03/27 17:26:17 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	init_anim(t_data *data, t_animation *anim, int size, char *path)
{
	int		i;
	char	*str;
	int		nb_sprite;

	nb_sprite = ft_strlen(path) - 6;
	anim->tab = malloc(size * sizeof(void *));
	if (!anim->tab)
		free_exit(data, "could not allocate anim");
	str = malloc((ft_strlen(path) + 1) * sizeof(char));
	if (!str)
		free_exit(data, "could not load anim");
	anim->size = size;
	anim->anim_sound = NULL;
	ft_strlcpy(str, path, ft_strlen(path) + 1);
	i = 0;
	while (i++ < size)
	{
		if (i >= 100 && i % 100 == 0)
			str[nb_sprite - 1] = '0' + i % 1000 / 100;
		str[nb_sprite] = '0' + (i % 100 / 10);
		str[nb_sprite + 1] = '0' + i % 10;
		anim->tab[i - 1] = mlx_png_file_to_image(data->mlx, str, NULL, NULL);
	}
	free(str);
}

void	init_idle(t_data *data)
{
	int	i;

	init_anim(data, &data->player.anim[0], 7, "sprites/idle/idle_r1_01.png");
	data->player.anim[0].name = "idle_r1";
	init_anim(data, &data->player.anim[1], 6, "sprites/idle/idle_r2_01.png");
	data->player.anim[1].name = "idle_r2";
	init_anim(data, &data->player.anim[2], 3, "sprites/idle/idle_r3_01.png");
	data->player.anim[2].name = "idle_r3";
	init_anim(data, &data->player.anim[3], 7, "sprites/idle/idle_l1_01.png");
	data->player.anim[3].name = "idle_l1";
	init_anim(data, &data->player.anim[4], 6, "sprites/idle/idle_l2_01.png");
	data->player.anim[4].name = "idle_l2";
	init_anim(data, &data->player.anim[5], 3, "sprites/idle/idle_l3_01.png");
	data->player.anim[5].name = "idle_l3";
	i = 0;
	while (i < 6)
	{
		data->player.anim[i].interval = 17;
		data->player.anim[i].index = 0;
		i++;
	}
}

void	init_move_anim(t_data *data)
{
	int	i;

	init_anim(data, &data->player.anim[6], 11, "sprites/walk/walk_r_01.png");
	data->player.anim[6].name = "walk_r";
	init_anim(data, &data->player.anim[7], 11, "sprites/walk/walk_l_01.png");
	data->player.anim[7].name = "walk_l";
	init_anim(data, &data->player.anim[8], 8, "sprites/run/run_r_01.png");
	data->player.anim[8].name = "run_r";
	init_anim(data, &data->player.anim[9], 8, "sprites/run/run_l_01.png");
	data->player.anim[9].name = "run_l";
	i = 6;
	while (i < 10)
	{
		data->player.anim[i].interval = 7;
		data->player.anim[i].index = 0;
		i++;
	}
}

void	init_default(t_data *data)
{
	int	i;

	init_anim(data, &data->player.anim[10], 1, "sprites/default_r_01.png");
	data->player.anim[10].name = "default_r";
	data->player.anim[10].interval = 180;
	data->player.anim[10].index = 0;
	data->player.anim[10].size = 1;
	init_anim(data, &data->player.anim[11], 1, "sprites/default_l_01.png");
	data->player.anim[11].name = "default_l";
	data->player.anim[11].interval = 180;
	data->player.anim[11].index = 0;
	data->player.anim[11].size = 1;
	init_anim(data, &data->player.anim[12], 17, "sprites/death/death_r_01.png");
	data->player.anim[12].name = "death_r";
	init_anim(data, &data->player.anim[13], 17, "sprites/death/death_l_01.png");
	data->player.anim[13].name = "death_l";
	i = 12;
	while (i < 14)
	{
		data->player.anim[i].interval = 10;
		data->player.anim[i].index = 0;
		i++;
	}
}

void	init_player_anim(t_data *data)
{
	int	i;

	i = 0;
	data->player.nb_anim = 14 + data->flags.touhou + (data->flags.fnaf * 2);
	data->player.anim = malloc(data->player.nb_anim * sizeof(t_animation));
	if (!data->player.anim)
		free_exit(data, "could not allocate anim");
	while (i < data->player.nb_anim)
	{
		data->player.anim[i].tab = NULL;
		data->player.anim[i].size = 0;
		i++;
	}
	init_idle(data);
	init_move_anim(data);
	init_default(data);
	init_flags_anim(data);
	data->player.default_sprite = mlx_png_file_to_image(data->mlx,
			"sprites/default_r_01.png",
			&data->player.size_x, &data->player.size_y);
	init_player(data);
}
