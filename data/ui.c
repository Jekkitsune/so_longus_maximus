/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 17:23:52 by fparis            #+#    #+#             */
/*   Updated: 2024/03/19 15:46:30 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	screen_effect(t_data *data, t_object *effect, int diff_x, int diff_y)
{
	int	x;
	int	y;

	x = data->win_x / 2 - effect->size_x / 2 + diff_x;
	y = data->win_y / 2 - effect->size_y / 2 + diff_y;
	mlx_put_image_to_window(data->mlx, data->win, effect->texture, x, y);
}

void	show_stamina(t_data *data)
{
	int	i;
	int	i2;
	int	size;
	int	size_y;

	size = 400;
	size_y = 30;
	i = 0;
	while (i < size)
	{
		i2 = 0;
		while (i2 < size_y)
		{
			if (i <= (data->player.stamina * size / data->player.max_stamina))
				mlx_pixel_put(data->mlx, data->win,
					data->win_x / 30 + i, data->win_y - data->win_y / 7
					+ i2, 0xAA00AA00);
			else
				mlx_pixel_put(data->mlx, data->win,
					data->win_x / 30 + i, data->win_y - data->win_y / 7
					+ i2, 0xAA555555);
			i2++;
		}
		i++;
	}
}

void	put_text(t_data *data, t_object *img, int y_shift, int time)
{
	int	x;
	int	y;

	if (time > -1)
	{
		data->ui.in_timer = img;
		data->ui.timer = time;
		data->ui.in_timer_y = y_shift;
	}
	if (img == get_tex(data, "number_01"))
		show_nb_left(data);
	else
	{
		x = data->win_x / 2 - img->size_x / 2 + get_diff_player(data, 1);
		y = data->win_y / 2 - data->player.size_y - y_shift
			+ get_diff_player(data, 0);
		mlx_put_image_to_window(data->mlx, data->win, img->texture, x, y);
	}
}

void	init_ui(t_data *data)
{
	data->ui.hide = 0;
	data->ui.timer = 0;
	data->ui.in_timer = NULL;
	data->ui.is_dark = 0;
	data->ui.meters = 0;
	data->ui.movement = 0;
	data->ui.dark.texture = mlx_png_file_to_image(data->mlx,
			"UI/Udark_03.png", &data->ui.dark.size_x, &data->ui.dark.size_y);
	data->ui.interact.texture = mlx_png_file_to_image(data->mlx,
			"UI/E.png", &data->ui.interact.size_x, &data->ui.interact.size_y);
	data->ui.shadow.texture = mlx_png_file_to_image(data->mlx,
			"UI/shadow3.png", &data->ui.shadow.size_x, &data->ui.shadow.size_y);
	data->ui.big_shadow.texture = mlx_png_file_to_image(data->mlx,
			"UI/shadow4.png", &data->ui.big_shadow.size_x,
			&data->ui.big_shadow.size_y);
	data->ui.hide_ui.texture = mlx_png_file_to_image(data->mlx,
			"UI/hide_ui.png", &data->ui.hide_ui.size_x,
			&data->ui.hide_ui.size_y);
	data->ui.red.texture = mlx_png_file_to_image(data->mlx,
			"UI/red.png", &data->ui.red.size_x,
			&data->ui.red.size_y);
	init_more_ui(data);
}

void	check_ui(t_data *data)
{
	t_UI	*ui;

	if (data->ui.hide || data->flags.debug_mode)
	{
		put_lumin_light(data, 1);
		if (data->flags.debug_mode)
			show_editor_text(data);
		return ;
	}
	ui = &data->ui;
	if (ui->timer <= 0)
		ui->in_timer = NULL;
	if (ui->in_timer)
		put_text(data, ui->in_timer, ui->in_timer_y, ui->timer - 1);
	else if (data->player.can_interact)
		put_text(data, &ui->interact, 20, -1);
	show_light_anim(data);
	put_lumin_light(data, 0);
	if (data->player.hidden)
		screen_effect(data, &data->ui.hide_ui,
			-get_diff_env(data, 1), -220 - get_diff_env(data, 0));
	show_stamina(data);
	show_meters(data);
	continue_heart_anim(data);
}
