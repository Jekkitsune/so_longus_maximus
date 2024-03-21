/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 15:20:33 by fparis            #+#    #+#             */
/*   Updated: 2024/03/21 19:16:45 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	check_special_object(t_data *data, int x, int y, char obj)
{
	if (obj == 'P')
		init_player_pos(data, x, y);
	else if (obj == ITEM)
		add_item(data, x, y);
	else if (obj == EXIT)
		init_exit_pos(data, x, y);
	else if (obj == HIDE)
		add_hideout(data, x, y);
	else if (obj == MONSTER)
		init_monster_pos(data, x, y);
	else
		data->map[x][y] = get_object(data, obj);
}

void	init_to_null(t_data *data)
{
	data->mlx = NULL;
	data->win = NULL;
	data->items = NULL;
	data->hideouts = NULL;
	data->map = NULL;
	data->chunk = NULL;
	data->player.anim = NULL;
	data->player.default_sprite = NULL;
	data->objects = NULL;
	data->player.x = -1;
	data->player.y = -1;
	data->exit_x = -1;
	data->exit_y = -1;
	data->monster.x = -1;
	data->monster.y = -1;
	data->monster.anim = NULL;
	data->monster.default_sprite = NULL;
	data->menu_list = NULL;
	data->fullscreen = 1;
	data->current_music = NULL;
	init_ui_to_null(data);
}

void	fill_map(t_data *data, char *map)
{
	int		fd;
	char	*line;
	int		x;
	int		y;

	fd = open(map, O_RDONLY);
	if (fd == -1)
		free_exit(data, "could not open map");
	line = get_next_line(fd);
	y = 0;
	while (y < data->size_y)
	{
		if (!line)
		{
			close(fd);
			free_exit(data, "gnl failed");
		}
		x = -1;
		while (x++ < data->size_x && line[x] && line[x] != '\n')
			check_special_object(data, x, y, line[x]);
		free(line);
		line = get_next_line(fd);
		y++;
	}
	close(fd);
}

void	init_data(t_data *data)
{
	init_to_null(data);
	data->mlx = mlx_init();
	if (!data->mlx)
		free_exit(data, "mlx failed");
	srand(time(NULL));
	init_objects_tab(data);
	data->tex_size = data->objects[0].size_x;
	init_player_anim(data);
	init_ui(data);
	data->win_x = 1920;
	data->win_y = 1080;
	load_save(data);
	data->win = mlx_new_window(data->mlx, data->win_x, data->win_y, "SI_LONG");
	mlx_set_fps_goal(data->mlx, 60);
	mlx_on_event(data->mlx, data->win, MLX_KEYDOWN, key_down_manager, data);
	mlx_on_event(data->mlx, data->win, MLX_KEYUP, key_up_manager, data);
	mlx_on_event(data->mlx, data->win, MLX_WINDOW_EVENT, window_manager, data);
	init_menus(data);
	mlx_loop_hook(data->mlx, game_loop, data);
}

void	init_textures(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	data->void_tex = get_tex(data, "black")->texture;
	while (y < data->size_y)
	{
		x = 0;
		while (x < data->size_x)
		{
			data->map[x][y] = get_good_tex(data, x, y);
			x++;
		}
		y++;
	}
}
