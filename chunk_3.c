/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chunk_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 19:04:58 by fparis            #+#    #+#             */
/*   Updated: 2024/02/27 16:49:32 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	check_chunk_load(t_data *data)
{
	if (data->center_x > data->tex_size / 2)
	{
		load_chunk(data, 1, 0);
		data->center_x = -(data->tex_size / 2)
			+ (data->center_x - (data->tex_size / 2));
	}
	else if (data->center_x < -(data->tex_size / 2))
	{
		load_chunk(data, -1, 0);
		data->center_x = (data->tex_size / 2)
			+ (data->center_x + (data->tex_size / 2));
	}
	if (data->center_y > data->tex_size / 2)
	{
		load_chunk(data, 0, 1);
		data->center_y = -(data->tex_size / 2)
			+ (data->center_y - (data->tex_size / 2));
	}
	else if (data->center_y < -(data->tex_size / 2))
	{
		load_chunk(data, 0, -1);
		data->center_y = (data->tex_size / 2)
			+ (data->center_y + (data->tex_size / 2));
	}
}
