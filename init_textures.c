/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 16:47:21 by fparis            #+#    #+#             */
/*   Updated: 2024/03/06 15:58:12 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	create_objects(t_data *data, char *img, int ind, int size)
{
	char	*str;
	int		nb_sprite;
	int		i;

	nb_sprite = ft_strlen(img) - 6;
	str = malloc((ft_strlen(img) + 1) * sizeof(char));
	if (!str)
		free_exit(data, "could not load object");
	ft_strlcpy(str, img, ft_strlen(img) + 1);
	i = 0;
	ind--;
	while (i < size)
	{
		i++;
		str[nb_sprite] = '0' + (i / 10);
		str[nb_sprite + 1] = '0' + i % 10;
		data->objects[ind + i].texture = mlx_png_file_to_image(data->mlx, str,
				&data->objects[ind + i].size_x, &data->objects[ind + i].size_y);
		data->objects[ind + i].name = ft_middle_str(str, 4, 4);
		data->objects[ind + i].density = 17;
	}
	free(str);
}

int	init_walls(t_data *data)
{
	int	i;

	data->objects[0].name = ft_strjoin("", "black");
	data->objects[0].texture = mlx_png_file_to_image(data->mlx, "tex/black.png",
			&data->objects[0].size_x, &data->objects[0].size_y);
	create_objects(data, "tex/corner_00.png", 1, 13);
	create_objects(data, "tex/wall_00.png", 14, 8);
	i = 0;
	while (i < 22)
	{
		data->objects[i].type = WALL;
		i++;
	}
	get_tex(data, "wall_04")->density = 3;
	return (i);
}

int	init_grounds(t_data *data, int index)
{
	int	i;

	i = index;
	create_objects(data, "tex/ground_00.png", index, 6);
	while (i < index + 6)
	{
		data->objects[i].type = GROUND;
		i++;
	}
	get_tex(data, "ground_04")->density = 1;
	get_tex(data, "ground_05")->density = 1;
	get_tex(data, "ground_06")->density = 1;
	return (i);
}

int	init_interactibles(t_data *data, int index)
{
	int	i;

	i = index;
	create_objects(data, "tex/item_00.png", index, 4);
	while (i < index + 4)
	{
		data->objects[i].type = ITEM;
		i++;
	}
	create_objects(data, "tex/exit_00.png", i, 2);
	while (i < index + 6)
	{
		data->objects[i].type = EXIT;
		i++;
	}
	create_objects(data, "tex/number_00.png", i, 11);
	i += 11;
	data->objects[i].name = ft_strjoin("", "hide");
	data->objects[i].texture = mlx_png_file_to_image(data->mlx,
			"tex/hide_01.png", &data->objects[i].size_x,
			&data->objects[i].size_y);
	data->objects[i].type = HIDE;
	data->objects[i].density = 10;
	return (i + 1);
}

void	init_objects_tab(t_data *data)
{
	int	i;
	int	index;

	data->nb_objects = 57;
	data->objects = malloc(sizeof(t_object) * data->nb_objects);
	if (!data->objects)
		free_exit(data, "could not allocate objects");
	i = 0;
	while (i < data->nb_objects)
	{
		data->objects[i].texture = NULL;
		data->objects[i].name = NULL;
		i++;
	}
	index = init_walls(data);
	index = init_grounds(data, index);
	index = init_interactibles(data, index);
	index = init_lumin_light(data, index);
}
