/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   distinct_paths.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: pacovali <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/12 18:56:23 by pacovali      #+#    #+#                 */
/*   Updated: 2019/01/23 17:53:36 by pacovali      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void		assign_distance1(t_map *map, int room_id, int dist)
{
	int			i;

	if ((map->rooms[room_id]->dist <= 0 || map->rooms[room_id]->dist > dist)
		&& room_id != map->start)
	{
		i = 0;
		if (room_id != map->stop)
			map->rooms[room_id]->dist = dist;
		while (map->rooms[room_id]->in_out[i] > 0)
		{
			if (map->rooms[room_id]->in_out[i] > 0
				&& map->rooms[room_id]->in_out[i] != map->stop
				&& map->rooms[room_id]->in_out[i] != map->start)
				assign_distance1(map, map->rooms[room_id]->in_out[i], dist + 1);
			i++;
		}
	}
}

static void	get_path(t_map *map, int r_id, int p_id, int prev_id)
{
	int		min;
	int		i;
	int		j[2];

	min = 999;
	i = 0;
	while (map->rooms[r_id]->in_out[i] > 0)
	{
		j[0] = map->rooms[r_id]->in_out[i];
		if (map->rooms[j[0]]->dist < min && j[0] != prev_id)
			j[1] = j[0];
		i++;
	}
	i = 0;
	while (i < 101 && map->path[p_id][i] != 0)
		i++;
	map->path[p_id][i] = j[1];
	if (i < 100 && j[1] != map->stop)
		get_path(map, j[1], p_id, r_id);
}

void		distinct_paths(t_map *map)
{
	int		i;

	assign_distance1(map, map->stop, 100);
	i = sort_connections(map, map->rooms[map->start]) + 2;
	map->path = (int**)ft_memalloc(sizeof(int*) * i);
	while (i > 0)
	{
		i--;
		map->path[i] = (int*)ft_memalloc(sizeof(int) * 102);
	}
	while (map->rooms[map->start]->in_out[i] > 0)
	{
		map->path[i][0] = map->rooms[map->start]->in_out[i];
		get_path(map, map->rooms[map->start]->in_out[i], i, map->start);
		i++;
	}
	assign_paths(map, 0, (int[]){0, 0, 0}, 999.0f);
}
