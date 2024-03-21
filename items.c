/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   items.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 17:43:59 by fparis            #+#    #+#             */
/*   Updated: 2024/02/29 11:57:18 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	init_items_tab(t_data *data)
{
	int	i;

	data->item_collected = 0;
	data->items = malloc(sizeof(t_item) * data->nb_items);
	if (!data->items)
		free_exit(data, "could not load items");
	i = 0;
	while (i < data->nb_items)
	{
		data->items[i].object = get_tex(data, "black");
		data->items[i].collected = 0;
		i++;
	}
}

void	add_item(t_data *data, int x, int y)
{
	int	i;

	i = 0;
	while (ft_strcmp(data->items[i].object->name, "black") != 0)
		i++;
	data->items[i].x = x;
	data->items[i].y = y;
	data->items[i].object = get_tex(data, get_random_tex(data->objects,
				tex_i(data, "item_01"), tex_i(data, "item_04")));
	data->map[x][y] = get_object(data, GROUND);
}

t_item	*has_item(t_data *data, int x, int y)
{
	int	i;

	i = 0;
	while (i < data->nb_items)
	{
		if (data->items[i].x == x && data->items[i].y == y
			&& !data->items[i].collected)
			return (&data->items[i]);
		i++;
	}
	return (NULL);
}
