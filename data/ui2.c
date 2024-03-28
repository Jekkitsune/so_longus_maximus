/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui2.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 21:08:11 by fparis            #+#    #+#             */
/*   Updated: 2024/03/06 15:25:08 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	put_nb(t_data *data, int nb, int x, int y)
{
	t_object	*img;

	img = &data->objects[tex_i(data, "number_01") + nb];
	mlx_put_image_to_window(data->mlx, data->win, img->texture, x, y);
}

void	show_nb_left(t_data *data)
{
	int	i;
	int	len;
	int	size;
	int	x;
	int	y;

	i = -1;
	len = ft_intlen(data->item_collected) + ft_intlen(data->nb_items) + 1;
	size = get_tex(data, "number_01")->size_x;
	x = data->win_x / 2 - (size * len) / 2 + get_diff_player(data, 1);
	y = data->win_y / 2 - data->player.size_y
		- data->ui.in_timer_y + get_diff_player(data, 0);
	while (++i < ft_intlen(data->item_collected))
	{
		put_nb(data, ft_revdigit(data->item_collected, i + 1), x, y);
		x += size;
	}
	put_nb(data, 10, x, y);
	x += size;
	i = -1;
	while (++i < ft_intlen(data->nb_items))
	{
		put_nb(data, ft_revdigit(data->nb_items, i + 1), x, y);
		x += size;
	}
}

void	show_meters(t_data *data)
{
	int	i;
	int	len;
	int	size;

	len = ft_intlen(data->ui.meters);
	size = get_tex(data, "number_01")->size_x;
	i = 0;
	while (i < len)
	{
		put_nb(data, ft_revdigit(data->ui.meters, i + 1),
			data->win_x / 30 + (i * size), data->win_y / 20);
		i++;
	}
}

void	add_meters(t_data *data, int x, int y)
{
	int	*tab;

	tab = data->player.movement;
	if (x < 0)
		x = -x;
	if (y < 0)
		y = -y;
	if (tab[0] && tab[2])
		y = 0;
	if (tab[1] && tab[3])
		x = 0;
	if (x > y)
		data->ui.movement += x;
	else
		data->ui.movement += y;
	if (data->ui.movement >= data->tex_size)
	{
		data->ui.meters += data->ui.movement / data->tex_size;
		data->ui.movement %= data->tex_size;
	}
}

void	init_more_ui(t_data *data)
{
	init_anim(data, &data->ui.heart_anim, 8, "UI/heart/heart_01.png");
	data->ui.heart_anim.clock = 0;
	data->ui.heart_anim.index = 0;
	data->ui.heart_anim.interval = 10;
	data->ui.is_dark = 0;
	data->ui.light_timer = rand() % 3000 + 1000;
	data->ui.in_anim = rand() % 3 + 1;
}
