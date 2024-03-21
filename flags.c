/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 17:40:00 by fparis            #+#    #+#             */
/*   Updated: 2024/03/20 17:27:18 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	is_map(char *str)
{
	int	i;

	i = ft_strlen(str);
	if (i < 5)
		return (0);
	if (str[i - 1] == 'r' && str[i - 2] == 'e' && str[i - 3] == 'b'
		&& str[i - 4] == '.')
		return (1);
	return (0);
}

void	check_flags(t_data *data, char **argv)
{
	int	i;

	i = 1;
	data->map_name = NULL;
	remove_all_flags(data);
	init_editor_tab(data);
	while (argv[i])
	{
		if (is_map(argv[i]) && !data->map_name)
			data->map_name = argv[i];
		else
		{
			ft_printf("Wrong parameters\n");
			exit(1);
		}
		i++;
	}
	if (!data->map_name)
		exit(1);
}

void	continue_long_anim(t_data *data, t_animation *current, char *name)
{
	char	*path;
	int		i_nb;

	if (current->clock < 0)
	{
		mlx_destroy_image(data->mlx, current->tab[current->index]);
		current->tab[current->index] = NULL;
		path = malloc(ft_strlen(name) + 1);
		if (!path)
			free_exit(data, "could not load long animation");
		ft_strlcpy(path, name, ft_strlen(name) + 1);
		current->index++;
		if (current->index >= current->size)
			current->index = 1;
		i_nb = ft_strlen(name) - 5;
		path[i_nb] = current->index % 10 + '0';
		path[i_nb - 1] = current->index % 100 / 10 + '0';
		path[i_nb - 2] = current->index % 1000 / 100 + '0';
		path[i_nb - 3] = current->index % 10000 / 1000 + '0';
		current->tab[current->index] = mlx_png_file_to_image(data->mlx,
				path, NULL, NULL);
		free(path);
		current->clock = current->interval;
	}
	data->player.sprite = current->tab[current->index];
}

void	init_bad_apple(t_data *data, t_animation *anim, int size)
{
	int	i;

	anim->tab = malloc(size * sizeof(void *));
	if (!anim->tab)
		free_exit(data, "could not load bad_apple");
	anim->size = size;
	i = 0;
	while (i < size)
	{
		anim->tab[i] = NULL;
		i++;
	}
	anim->name = "bad_apple";
	anim->interval = 10;
	anim->index = 0;
	anim->clock = anim->interval;
	anim->tab[0] = mlx_png_file_to_image(data->mlx,
			"sprites/ba/frame_0001.png", NULL, NULL);
}

void	bad_apple_manager(t_data *data)
{
	if (data->flags.bad_apple_launched)
	{
		data->player.hitbox_x /= 2;
		data->flags.bad_apple_launched = 0;
		idle_anim(data);
	}
	else if (!data->player.dead)
	{
		data->player.hitbox_x *= 2;
		change_anim(data, "bad_apple", 0);
		data->flags.bad_apple_launched = 1;
	}
}
