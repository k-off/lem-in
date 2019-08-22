/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   crossing_paths.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: pacovali <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/12 18:56:23 by pacovali      #+#    #+#                 */
/*   Updated: 2019/01/23 17:53:36 by pacovali      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static void	assign_room2(t_map *map, int id, int dist)
{
	int		i;

	i = 0;
	if (id == map->stop)
		return ;
	while (map->rooms[id]->in_out[i] > 0)
	{
		if (map->rooms[map->rooms[id]->in_out[i]]->dist < 1)
		{
			map->rooms[map->rooms[id]->in_out[i]]->dist = dist;
			if (id == map->start)
				map->rooms[map->rooms[id]->in_out[i]]->path_id = \
				map->rooms[id]->in_out[i];
			else
				map->rooms[map->rooms[id]->in_out[i]]->path_id = \
				map->rooms[id]->path_id;
		}
		i++;
	}
}

void		assign_distance2(t_map *map, int id, int dist)
{
	int			i;

	if (dist == 100)
		assign_room2(map, map->start, dist - 1);
	else
	{
		i = 0;
		while (i < 2097151)
		{
			if (map->rooms[i] && map->rooms[i]->dist == dist && dist > 0)
				assign_room2(map, i, dist - 1);
			i++;
		}
	}
	if (dist > 0)
		assign_distance2(map, id, dist - 1);
	map->rooms[map->start]->dist = 100;
	map->rooms[map->stop]->dist = 0;
}

void		check_dup(int **path, int *nr)
{
	int		i;

	i = 0;
	while (i < *nr)
	{
		if (path[i][0] == path[*nr][0])
		{
			path[*nr][0] = 0;
			(*nr)--;
			break ;
		}
		i++;
	}
}

void		get_xpath(t_map *map, int id, int **path, int dist)
{
	int		i;
	int		*tmp;

	i = 0;
	tmp = (int[]){0, 0};
	while (map->rooms[id]->in_out[i] > 0)
	{
		if (map->rooms[map->rooms[id]->in_out[i]]->path_id == path[0][0]
			&& map->rooms[map->rooms[id]->in_out[i]]->dist > dist
			&& map->rooms[map->rooms[id]->in_out[i]]->dist > tmp[1])
		{
			tmp[0] = map->rooms[id]->in_out[i];
			tmp[1] = map->rooms[map->rooms[id]->in_out[i]]->dist;
		}
		i++;
	}
	if (tmp[0] != 0 && tmp[1] > dist)
		path[0][99 - tmp[1]] = tmp[0];
	if (tmp[0] != 0 && tmp[1] > dist && dist == 0)
		path[0][100 - tmp[1]] = map->stop;
	if (tmp[0] != 0 && tmp[1] > dist && tmp[1] < 99)
		get_xpath(map, tmp[0], path, tmp[1]);
}

void		crossing_paths(t_map *map)
{
	int		i;
	int		j;

	i = 101;
	assign_distance2(map, map->stop, 100);
	map->path = (int**)ft_memalloc(sizeof(int*) * 101);
	while (i > 0)
	{
		i--;
		map->path[i] = (int*)ft_memalloc(sizeof(int) * 101);
	}
	j = 0;
	while (map->rooms[map->stop]->in_out[i] > 0)
	{
		map->path[j][0] = map->rooms[map->rooms[map->stop]->in_out[i]]->path_id;
		check_dup(map->path, &j);
		j++;
		get_xpath(map, map->stop, &(map->path[j - 1]), 0);
		map->path[j][0] = 0;
		i++;
	}
	assign_paths(map, 0, (int[]){0, 0, 0}, 999.0f);
}
