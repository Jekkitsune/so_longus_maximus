/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags_4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 22:54:47 by fparis            #+#    #+#             */
/*   Updated: 2024/03/09 00:05:56 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	init_hideouts_tab_without_exit_program(t_data *data)
{
	int	i;

	data->hideouts = malloc(sizeof(t_hideout) * data->nb_hideout);
	if (!data->hideouts)
		return ;
	i = 0;
	while (i < data->nb_hideout)
	{
		data->hideouts[i].object = get_tex(data, "black");
		i++;
	}
}

void	realloc_hide(t_data *data, int add)
{
	int			last_size;
	int			i;
	t_hideout	*last_tab;

	last_size = data->nb_hideout;
	data->nb_hideout += add;
	last_tab = data->hideouts;
	init_hideouts_tab_without_exit_program(data);
	i = 0;
	while (last_tab && data->hideouts && i < last_size)
	{
		if (ft_strcmp(last_tab[i].object->name, "black") != 0)
			add_hideout(data, last_tab[i].x, last_tab[i].y);
		i++;
	}
	free(last_tab);
}

void	editor_place_hide(t_data *data)
{
	if (has_hideout(data, data->player.x, data->player.y) != NULL)
		return ;
	editor_place_ground(data);
	if (is_type(data, data->player.x, data->player.y, GROUND))
	{
		realloc_hide(data, 1);
		add_hideout(data, data->player.x, data->player.y);
	}
}

void	editor_remove_hide(t_data *data)
{
	t_hideout	*hide;

	hide = has_hideout(data, data->player.x, data->player.y);
	if (hide)
	{
		hide->object = get_tex(data, "black");
		realloc_hide(data, -1);
	}
}

void	editor_place_exit(t_data *data)
{
	if (data->player.x == data->exit_x
		&& data->player.y == data->exit_y)
		return ;
	editor_place_ground(data);
	data->exit_x = data->player.x;
	data->exit_y = data->player.y;
}
