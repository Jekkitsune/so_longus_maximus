/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 23:18:24 by fparis            #+#    #+#             */
/*   Updated: 2024/03/19 18:08:10 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	parse_line(t_data *data, char *line, int fd)
{
	int	i;

	if (!line)
	{
		close(fd);
		free_exit(data, "gnl error");
	}
	i = 0;
	while (line[i] == '0' || line[i] == '1' || line[i] == 'C'
		|| line[i] == 'E' || line[i] == 'P' || line[i] == 'H' || line[i] == 'M')
	{
		if (line[i] == 'C')
			data->nb_items++;
		if (line[i] == 'H')
			data->nb_hideout++;
		if (i == 2147483647 || data->nb_items == 2147483647)
			free_gnl(data, fd, line);
		i++;
	}
	if (line[i] != '\0' && line[i] != '\n')
		free_gnl(data, fd, line);
	return (i);
}

void	check_map(t_data *data, char *map)
{
	char	*line;
	int		fd;

	fd = open(map, O_RDONLY);
	if (fd == -1)
		free_exit(data, "could not open map");
	line = get_next_line(fd);
	data->size_x = parse_line(data, line, fd);
	data->size_y = 1;
	free(line);
	line = get_next_line(fd);
	while (line)
	{
		if (data->size_x != parse_line(data, line, fd)
			|| data->size_y == 2147483647)
			free_gnl(data, fd, line);
		data->size_y++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
}

void	init_map(t_data	*data, char *map)
{
	int	i;

	data->nb_items = 0;
	data->nb_hideout = 0;
	check_map(data, map);
	if (data->size_x == 0)
		free_exit(data, "map has x = 0");
	data->map = malloc((data->size_x) * sizeof(t_object *));
	if (!data->map)
		free_exit(data, "could not allocate map");
	i = 0;
	while (i < data->size_x)
	{
		data->map[i] = malloc((data->size_y) * sizeof(t_object *));
		if (!data->map[i])
			free_exit(data, "could not allocate map");
		i++;
	}
}

int	is_finishable(t_data *data, int player_x, int player_y)
{
	int	i;
	int	p_coord[2];
	int	coord_2[2];

	p_coord[0] = player_x;
	p_coord[1] = player_y;
	if (!can_go_to(data, p_coord,
			get_coord(coord_2, data->exit_x, data->exit_y)))
		return (0);
	i = 0;
	while (i < data->nb_items)
	{
		if (!can_go_to(data, p_coord,
				get_coord(coord_2, data->items[i].x, data->items[i].y)))
			return (0);
		i++;
	}
	return (1);
}

void	is_correct_map(t_data *data)
{
	int	i;
	int	i2;

	i = 0;
	while (i < data->size_x)
	{
		i2 = 0;
		while (i2 < data->size_y)
		{
			if ((i == 0 || i == data->size_x - 1
					|| i2 == 0 || i2 == data->size_y - 1)
				&& data->map[i][i2]->type != WALL)
				free_exit(data, "limits are not walls");
			i2++;
		}
		i++;
	}
	if (data->player.x == -1 || data->exit_x == -1 || data->nb_items <= 0)
		free_exit(data, "not enough item/player/exit");
	if (data->player.x == -2 || data->exit_x == -2)
		free_exit(data, "too many player/exit");
	if (is_finishable(data, data->player.x, data->player.y) == 0)
		free_exit(data, "map is not finishable");
}
