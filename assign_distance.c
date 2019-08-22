/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   assign_paths.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: pacovali <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/12 18:56:23 by pacovali      #+#    #+#                 */
/*   Updated: 2019/01/23 17:53:36 by pacovali      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	assign_distance3a(t_map *map, int room_id, int dist)
{
	int			i;

	i = 0;
	if (room_id != map->stop)
		map->rooms[room_id]->dist = dist;
	while (map->rooms[room_id]->in_out[i] > 0)
	{
		if (map->rooms[room_id]->in_out[i] != map->stop
			&& map->rooms[room_id]->in_out[i] != map->start
			&& map->rooms[map->rooms[room_id]->in_out[i]]->dist < 1)
			map->rooms[map->rooms[room_id]->in_out[i]]->dist = dist + 1;
		i++;
	}
	i = 0;
	while (map->rooms[room_id]->in_out[i] > 0)
	{
		if (map->rooms[map->rooms[room_id]->in_out[i]]->dist >= dist
			&& map->rooms[room_id]->in_out[i] != map->start
			&& map->rooms[room_id]->in_out[i] != map->stop)
			assign_distance3a(map, map->rooms[room_id]->in_out[i], dist + 1);
		i++;
	}
}

void	assign_distance3b(t_map *map, int room_id, int dist)
{
	int			i;

	i = 0;
	if (room_id != map->start)
		map->rooms[room_id]->dist2 = dist;
	while (map->rooms[room_id]->in_out[i] > 0)
	{
		if (map->rooms[room_id]->in_out[i] != map->stop
			&& map->rooms[room_id]->in_out[i] != map->start
			&& map->rooms[map->rooms[room_id]->in_out[i]]->dist2 < 1)
			map->rooms[map->rooms[room_id]->in_out[i]]->dist2 = dist + 1;
		i++;
	}
	i = 0;
	while (map->rooms[room_id]->in_out[i] > 0)
	{
		if (map->rooms[map->rooms[room_id]->in_out[i]]->dist2 >= dist
			&& map->rooms[room_id]->in_out[i] != map->start
			&& map->rooms[room_id]->in_out[i] != map->stop)
			assign_distance3b(map, map->rooms[room_id]->in_out[i], dist + 1);
		i++;
	}
}
