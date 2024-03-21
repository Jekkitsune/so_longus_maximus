/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 19:28:10 by fparis            #+#    #+#             */
/*   Updated: 2024/03/19 18:12:45 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	destroy_heart_anim(t_data *data)
{
	int	i;

	if (data->ui.heart_anim.tab)
	{
		i = 0;
		while (i < data->ui.heart_anim.size)
		{
			if (data->ui.heart_anim.tab[i])
				mlx_destroy_image(data->mlx, data->ui.heart_anim.tab[i]);
			i++;
		}
	}
}

void	free_menus(t_data *data)
{
	int	i;

	if (data->menu_list)
	{
		i = 0;
		while (i < data->nb_menu && data->menu_list[i].tab)
		{
			free(data->menu_list[i].tab);
			i++;
		}
		free(data->menu_list);
	}
}

void	free_textures(t_data *data)
{
	int	i;

	if (data->objects)
	{
		i = 0;
		while (i < data->nb_objects)
		{
			if (data->objects[i].name)
				free(data->objects[i].name);
			i++;
		}
		free(data->objects);
	}
}
