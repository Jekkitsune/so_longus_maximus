/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 20:06:17 by fparis            #+#    #+#             */
/*   Updated: 2024/02/29 12:04:04 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	in_bound(t_data *data, int x, int y)
{
	return (x >= 0 && x < data->size_x && y >= 0 && y < data->size_y);
}

int	is_type(t_data *data, int x, int y, char type)
{
	return (x >= 0 && x < data->size_x && y >= 0 && y < data->size_y
		&& data->map[x][y]->type == type);
}

int	*get_coord(int res[2], int x, int y)
{
	res[0] = x;
	res[1] = y;
	return (res);
}

void	free_gnl(t_data *data, int fd, char *line)
{
	while (line)
	{
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	free_exit(data, "parsing");
}

void	*make_img(t_data *data, char *filename, int *width, int *height)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		free_exit(data, filename);
	else
	{
		close(fd);
		return (mlx_png_file_to_image(data->mlx, filename, width, height));
	}
	return (NULL);
}
