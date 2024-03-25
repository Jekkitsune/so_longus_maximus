/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 20:21:33 by fparis            #+#    #+#             */
/*   Updated: 2024/03/21 21:18:18 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	save(t_data *data)
{
	int	fd;

	fd = open("save", O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return ;
	if (data->ui.luminosity)
	{
		ft_putstr_fd("\nluminosity\n", fd);
		ft_putstr_fd(data->ui.luminosity->name, fd);
	}
	if (data->ui.light)
	{
		ft_putstr_fd("\nlight\n", fd);
		ft_putstr_fd(data->ui.light->name, fd);
	}
	ft_putstr_fd("\nfullscreen\n", fd);
	ft_putstr_fd(ft_itoa(data->fullscreen), fd);
	ft_putstr_fd("\n", fd);
	close(fd);
}

void	load_luminosity(t_data *data, char **line, int fd)
{
	int	nb;

	free(*line);
	*line = get_next_line(fd);
	if (*line && ft_strncmp(*line, "dark_", 5) == 0)
	{
		nb = ft_atoi(*line + 5);
		if (nb >= 1 && nb <= 3)
			data->ui.luminosity
				= &data->objects[tex_i(data, "dark_01") + nb - 1];
	}
}

void	load_light(t_data *data, char **line, int fd)
{
	int	nb;

	free(*line);
	*line = get_next_line(fd);
	if (*line && ft_strncmp(*line, "light_effect_", 13) == 0)
	{
		nb = ft_atoi(*line + 13);
		if (nb >= 1 && nb <= 8)
			data->ui.light
				= &data->objects[tex_i(data, "light_effect_01") + nb - 1];
	}
}

void	load_fullscreen(t_data *data, char **line, int fd)
{
	int	nb;

	free(*line);
	*line = get_next_line(fd);
	nb = ft_atoi(*line);
	if (nb == 0 || nb == 1)
		data->fullscreen = nb;
	if (!data->fullscreen)
	{
		data->win_x = 1920 - 600;
		data->win_y = 1080 - 400;
	}
}

void	load_save(t_data *data)
{
	int		fd;
	char	*line;

	fd = open("save", O_RDWR);
	if (fd < 0)
		return ;
	line = get_next_line(fd);
	while (line)
	{
		if (line && ft_strncmp(line, "luminosity", 10) == 0)
			load_luminosity(data, &line, fd);
		if (line && ft_strncmp(line, "light", 5) == 0)
			load_light(data, &line, fd);
		if (line && ft_strncmp(line, "fullscreen", 10) == 0)
			load_fullscreen(data, &line, fd);
		if (line)
		{
			free(line);
			line = get_next_line(fd);
		}
	}
}
