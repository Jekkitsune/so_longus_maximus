/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags_6.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 15:38:17 by fparis            #+#    #+#             */
/*   Updated: 2024/03/19 18:07:10 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	show_editor_text(t_data *data)
{
	char	*txt;
	char	*txt2;
	char	*txt3;

	txt = "<- / -> : change object";
	txt2 = "E : put object";
	txt3 = "Space : save map";
	mlx_string_put(data->mlx, data->win, 10, 50, 0xFFFFFF00, txt);
	mlx_string_put(data->mlx, data->win, 10, 100, 0xFFFFFF00, txt2);
	mlx_string_put(data->mlx, data->win, 10, 150, 0xFFFFFF00, txt3);
	if (data->flags.editor_custom_exist)
		mlx_string_put(data->mlx, data->win, 10, 200, 0xFFEE0000,
			"Warning : 'custom.ber' already exist!!");
	else if (data->flags.editor_warning)
		mlx_string_put(data->mlx, data->win, 10, 200, 0xFFEE0000,
			data->flags.editor_warning);
	if (data->flags.editor_saved == 1)
		mlx_string_put(data->mlx, data->win, 10, 250, 0xFF00EE00,
			"Map was successfully saved !");
}

char	*check_custom_map_error(t_data *data)
{
	data->flags.editor_custom_exist = 0;
	if (data->flags.editor_p_x < 0 || data->flags.editor_p_x >= data->size_x
		|| data->flags.editor_p_y < 0 || data->flags.editor_p_y >= data->size_y)
		return ("Warning : player starting position is incorrect!");
	if (data->exit_x < 0 || data->exit_x >= data->size_x
		|| data->exit_y < 0 || data->exit_y >= data->size_y)
		return ("Warning : exit position is incorrect!");
	if (data->nb_items == 0)
		return ("Warning : not enough items");
	if (!is_finishable(data, data->flags.editor_p_x, data->flags.editor_p_y))
		return ("Warning : map is not finishable!");
	if (data->monster.x < 0 || data->monster.x >= data->size_x
		|| data->monster.y < 0 || data->monster.y >= data->size_y)
		return ("Warning : no monster in the map!");
	return (NULL);
}

void	write_custom_map(t_data *data, int fd, int x, int y)
{
	if (has_hideout(data, x, y))
		ft_putstr_fd("H", fd);
	else if (has_item(data, x, y))
		ft_putstr_fd("C", fd);
	else if (x == data->flags.editor_p_x && y == data->flags.editor_p_y)
		ft_putstr_fd("P", fd);
	else if (x == data->monster.x && y == data->monster.y)
		ft_putstr_fd("M", fd);
	else if (x == data->exit_x && y == data->exit_y)
		ft_putstr_fd("E", fd);
	else if (is_type(data, x, y, WALL))
		ft_putstr_fd("1", fd);
	else if (is_type(data, x, y, GROUND))
		ft_putstr_fd("0", fd);
}

void	save_custom_map(t_data *data)
{
	int	fd;
	int	x;
	int	y;

	fd = open("custom.ber", O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		data->flags.editor_warning = "Warning : can't save map ;(";
	else
	{
		y = 0;
		while (y < data->size_y)
		{
			x = 0;
			while (x < data->size_x)
			{
				write_custom_map(data, fd, x, y);
				x++;
			}
			ft_putstr_fd("\n", fd);
			y++;
		}
		data->flags.editor_warning = check_custom_map_error(data);
		close(fd);
		data->flags.editor_saved = 1;
	}
}
