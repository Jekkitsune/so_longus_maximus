/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 16:05:43 by fparis            #+#    #+#             */
/*   Updated: 2024/03/20 17:24:01 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	load_old_tex(t_data *data)
{
	int	i;

	if (!data->flags.old_tex)
		return ;
	load_old_wall(data);
	i = tex_i(data, "black");
	mlx_destroy_image(data->mlx, data->objects[i].texture);
	data->objects[i].texture = mlx_png_file_to_image(data->mlx,
			"tex/dev_tex/void.png", &data->objects[i].size_x,
			&data->objects[i].size_y);
	i = get_anim_index(data, "default_r");
	mlx_destroy_image(data->mlx, data->player.anim[i].tab[0]);
	data->player.anim[i].tab[0] = mlx_png_file_to_image(data->mlx,
			"tex/dev_tex/player.png", &data->player.size_x,
			&data->player.size_y);
	data->tex_size = data->objects[0].size_x;
}

void	init_editor_tab(t_data *data)
{
	int	fd;

	data->flags.editor_tab[0] = GROUND;
	data->flags.editor_tab[1] = WALL;
	data->flags.editor_tab[2] = HIDE;
	data->flags.editor_tab[3] = ITEM;
	data->flags.editor_tab[4] = EXIT;
	data->flags.editor_tab[5] = PLAYER;
	data->flags.editor_tab[6] = MONSTER;
	data->flags.editor_index = 0;
	data->flags.editor_p_x = 0;
	data->flags.editor_p_y = 0;
	data->flags.editor_warning = NULL;
	data->flags.editor_saved = 0;
	fd = open("custom.ber", O_RDONLY);
	if (fd != -1)
	{
		close(fd);
		data->flags.editor_custom_exist = 1;
	}
	else
		data->flags.editor_custom_exist = 0;
}

void	change_editor(t_data *data, int nb)
{
	data->flags.editor_index += nb;
	if (data->flags.editor_index < 0)
		data->flags.editor_index = 6;
	if (data->flags.editor_index > 6)
		data->flags.editor_index = 0;
	if (data->flags.editor_tab[data->flags.editor_index] == PLAYER)
		data->player.sprite = data->player.default_sprite;
	else if (data->flags.editor_tab[data->flags.editor_index] == MONSTER)
		data->player.sprite = data->monster.default_sprite;
	else if (data->flags.editor_tab[data->flags.editor_index] == WALL)
		data->player.sprite = get_tex(data, "wall_01")->texture;
	else
		data->player.sprite = get_object(data,
				data->flags.editor_tab[data->flags.editor_index])->texture;
}

void	debug_command(t_data *data, int key)
{
	if (key == 8)
		editor_place(data);
	if (key == 79)
		change_editor(data, 1);
	if (key == 80)
		change_editor(data, -1);
	if (key == 44)
		save_custom_map(data);
}

void	remove_all_flags(t_data *data)
{
	data->flags.touhou = 0;
	data->flags.bad_apple_launched = 0;
	data->flags.old_tex = 0;
	data->flags.debug_mode = 0;
	data->flags.fnaf = 0;
}
