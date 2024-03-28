/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 16:19:24 by fparis            #+#    #+#             */
/*   Updated: 2024/03/08 22:18:53 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

t_object	*get_tex(t_data *data, char *name)
{
	int	i;

	i = 0;
	while (i < data->nb_objects && data->objects[i].texture
		&& ft_strcmp(name, data->objects[i].name) != 0)
		i++;
	if (i >= data->nb_objects)
		return (&data->objects[0]);
	return (&data->objects[i]);
}

t_object	*get_object(t_data *data, char type)
{
	int	i;

	i = 0;
	while (i < data->nb_objects && data->objects[i].type != type)
		i++;
	return (&data->objects[i]);
}

char	*get_random_tex(t_object *tab, int start, int end)
{
	int	size;
	int	i;
	int	random;

	i = start;
	size = 0;
	while (i <= end)
	{
		size += tab[i].density;
		i++;
	}
	if (size < 0)
		return (NULL);
	random = rand() % size;
	i = start;
	size = 0;
	while (i <= end)
	{
		if (random >= size && random < size + tab[i].density)
			return (tab[i].name);
		size += tab[i].density;
		i++;
	}
	return (tab[i].name);
}

t_object	*get_good_tex(t_data *data, int x, int y)
{
	if (data->flags.old_tex)
	{
		if (data->map[x][y]->type == WALL && is_type(data, x, y + 1, WALL))
			return (get_tex(data, "wall_02"));
		else if (data->map[x][y]->type == WALL)
			return (get_tex(data, "wall_01"));
		else if (data->map[x][y]->type == GROUND)
			return (get_tex(data, "ground_01"));
	}
	if (data->map[x][y]->type == WALL)
		return (get_wall(data, x, y));
	if (data->map[x][y]->type == GROUND)
	{
		return (get_tex(data, get_random_tex(data->objects,
					tex_i(data, "ground_01"), tex_i(data, "ground_06"))));
	}
	return (NULL);
}

int	tex_i(t_data *data, char *name)
{
	int	i;

	i = 0;
	while (i < data->nb_objects && data->objects[i].texture
		&& ft_strcmp(name, data->objects[i].name) != 0)
		i++;
	if (i >= data->nb_objects)
		return (0);
	return (i);
}
