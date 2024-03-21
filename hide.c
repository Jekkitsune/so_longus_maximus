/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hide.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 23:10:55 by fparis            #+#    #+#             */
/*   Updated: 2024/03/19 18:03:50 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	init_hideouts_tab(t_data *data)
{
	int	i;

	data->hideouts = malloc(sizeof(t_hideout) * data->nb_hideout);
	if (!data->hideouts)
		free_exit(data, "could not allocate hideouts");
	i = 0;
	while (i < data->nb_hideout)
	{
		data->hideouts[i].object = get_tex(data, "black");
		i++;
	}
}

void	add_hideout(t_data *data, int x, int y)
{
	int	i;

	i = 0;
	while (ft_strcmp(data->hideouts[i].object->name, "black") != 0)
		i++;
	data->hideouts[i].x = x;
	data->hideouts[i].y = y;
	data->hideouts[i].object = get_tex(data, "hide");
	data->map[x][y] = get_object(data, GROUND);
}

t_hideout	*has_hideout(t_data *data, int x, int y)
{
	int	i;

	i = 0;
	while (i < data->nb_hideout)
	{
		if (data->hideouts[i].x == x && data->hideouts[i].y == y)
			return (&data->hideouts[i]);
		i++;
	}
	return (NULL);
}

void	hideout_collision(t_data *data, int *x, int *y)
{
	int	y_up;

	y_up = data->center_y - data->player.hitbox_y + *y;
	if (has_hideout(data, data->player.x, data->player.y))
	{
		if (*y < 0 && y_up < -70 && (data->center_x - data->player.hitbox_x < 30
				&& data->center_x + data->player.hitbox_x > -30))
			*y = -(data->center_y - data->player.hitbox_y + 70);
		if (y_up < -70 && *x > 0
			&& data->center_x + data->player.hitbox_x + *x > -30
			&& data->center_x + data->player.hitbox_x < 30)
			*x = -(data->center_x + data->player.hitbox_x + 30);
		else if (y_up < -70 && *x < 0
			&& data->center_x - data->player.hitbox_x + *x < 30
			&& data->center_x - data->player.hitbox_x > -30)
			*x = -(data->center_x - data->player.hitbox_x - 30);
	}
	else if (has_hideout(data, data->player.x, data->player.y + 1))
	{
		if (*y > 0 && data->center_y + data->player.hitbox_y
			+ *y > (data->tex_size / 2)
			&& (data->center_x - data->player.hitbox_x < 30
				&& data->center_x + data->player.hitbox_x > -30))
			*y = (data->tex_size / 2) - data->center_y - data->player.hitbox_y;
	}
}

void	hide(t_data *data)
{
	if (data->player.hidden)
	{
		data->player.hidden = 0;
		data->player.hidden_fr = 0;
	}
	else
	{
		stun_player(data, 40);
		data->player.hidden = 1;
		if (data->monster.exist
			&& !last_seen_x_y(data, data->player.x, data->player.y))
			data->player.hidden_fr = 1;
		data->center_x = 0;
	}
}
