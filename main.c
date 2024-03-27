/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 18:34:02 by fparis            #+#    #+#             */
/*   Updated: 2024/03/27 22:55:13 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	game_loop(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	continue_music(data);
	if (data->current_menu)
		show_current_menu(data);
	else
	{
		player_loop(data);
		continue_player_anim(data);
		if (data->monster.exist && !data->flags.debug_mode)
		{
			continue_monster_anim(data, &data->monster);
			monster_move(data);
		}
		if (data->flags.car)
			continue_all_effects(data);
		show_chunk(data);
		check_ui(data);
		anim_sound_loop(data);
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc < 2)
	{
		ft_printf("Not enough maps");
		return (1);
	}
	check_flags(&data, argv, argc);
	init_data(&data);
	mlx_loop(data.mlx);
	mlx_clear_window(data.mlx, data.win);
	destroy_all_img(&data);
	free_all_data(&data);
	stop_music(&data);
	mlx_destroy_window(data.mlx, data.win);
	mlx_destroy_display(data.mlx);
	return (0);
}
