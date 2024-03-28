/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfinding.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 13:53:32 by fparis            #+#    #+#             */
/*   Updated: 2024/02/29 12:03:12 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	free_path(t_path *path)
{
	if (!path)
		return ;
	free_path(path->next);
	free(path);
}

t_path	*new_path(t_data *data, int x, int y, t_path **path)
{
	t_path	*new;

	new = malloc(sizeof(t_path));
	if (!new)
	{
		free_path(*path);
		free_exit(data, "could not allocate path");
	}
	new->x = x;
	new->y = y;
	new->next = NULL;
	if (path && *path)
	{
		new->goal_x = (*path)->goal_x;
		new->goal_y = (*path)->goal_y;
		new->next = *path;
		*path = new;
	}
	return (new);
}

int	was_traveled(t_path *path, int x, int y)
{
	while (path)
	{
		if (path->x == x
			&& path->y == y)
			return (1);
		path = path->next;
	}
	return (0);
}

int	can_connect(t_data *data, int x, int y, t_path **path)
{
	if (!is_type(data, x, y, GROUND) || was_traveled(*path, x, y))
		return (0);
	else if (x == (*path)->goal_x && y == (*path)->goal_y)
		return (1);
	new_path(data, x, y, path);
	if (can_connect(data, x + 1, y, path) || can_connect(data, x - 1, y, path)
		|| can_connect(data, x, y + 1, path)
		|| can_connect(data, x, y - 1, path))
		return (1);
	return (0);
}

int	can_go_to(t_data *data, int *coord_1, int *coord_2)
{
	t_path	*path;
	int		res;

	path = new_path(data, coord_1[0], coord_1[1], NULL);
	path->goal_x = coord_2[0];
	path->goal_y = coord_2[1];
	res = (can_connect(data, coord_1[0] + 1, coord_1[1], &path)
			|| can_connect(data, coord_1[0] - 1, coord_1[1], &path)
			|| can_connect(data, coord_1[0], coord_1[1] + 1, &path)
			|| can_connect(data, coord_1[0], coord_1[1] - 1, &path));
	free_path(path);
	return (res);
}
