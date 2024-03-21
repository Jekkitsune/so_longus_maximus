/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 20:18:40 by fparis            #+#    #+#             */
/*   Updated: 2024/03/21 18:14:44 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	free_map_chunk(t_data *data)
{
	int	i;

	if (data->map)
	{
		i = 0;
		while (i < data->size_x && data->map[i])
		{
			free(data->map[i]);
			i++;
		}
		free(data->map);
	}
	if (data->chunk)
	{
		i = 0;
		while (i < data->chunk_size && data->chunk[i])
		{
			free(data->chunk[i]);
			i++;
		}
		free(data->chunk);
	}
}

void	free_animations(t_data *data)
{
	int	i;

	if (data->player.anim)
	{
		i = 0;
		while (i < data->player.nb_anim && data->player.anim[i].tab)
		{
			free(data->player.anim[i].tab);
			i++;
		}
		free(data->player.anim);
	}
}

void	free_monster(t_data *data)
{
	int	i;

	if (data->monster.anim)
	{
		i = 0;
		while (i < data->monster.nb_anim && data->monster.anim[i].tab)
		{
			free(data->monster.anim[i].tab);
			i++;
		}
		free(data->monster.anim);
	}
}

void	free_all_data(t_data *data)
{
	if (data->items)
		free(data->items);
	if (data->hideouts)
		free(data->hideouts);
	if (data->ui.heart_anim.tab)
		free(data->ui.heart_anim.tab);
	free_map_chunk(data);
	free_animations(data);
	free_textures(data);
	free_monster(data);
	free_menus(data);
}

void	free_exit(t_data *data, char *error)
{
	destroy_all_img(data);
	free_all_data(data);
	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
	if (data->mlx)
		mlx_destroy_display(data->mlx);
	stop_music(data);
	ft_printf("so_long error: %s\n", error);
	exit(1);
}
