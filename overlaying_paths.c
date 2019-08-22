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

static int	compare_rooms(t_map *map, int found, int conn, int id)
{
	if (map->rooms[conn] == NULL || map->rooms[conn]->path_id != 0)
		return (0);
	if (conn == map->start)
		return (0);
	if (found == id)
		return (1);
	else if (map->rooms[conn]->dist2 <= map->rooms[found]->dist2 &&
			map->rooms[conn]->dist >= map->rooms[found]->dist)
		return (1);
	return (0);
}

static int	add_room(t_map *map, int path_nr, int len, int id)
{
	int		i;
	int		conn;
	int		found;

	i = 0;
	found = id;
	sort_connections2(map, map->rooms[id]);
	while (map->rooms[id]->in_out[i] > 0 && i < 100)
	{
		conn = map->rooms[id]->in_out[i];
		if (compare_rooms(map, found, conn, id) > 0)
			found = conn;
		i++;
	}
	if (found != id)
	{
		if (found != map->stop)
			map->rooms[found]->path_id = map->rooms[id]->path_id;
		map->path[path_nr][len] = found;
		if (map->path[path_nr][len] == map->stop && map->path[path_nr][0] > 0)
			map->path[path_nr][0] = -map->path[path_nr][0];
	}
	return (found != id);
}

static void	create_paths2(t_map *map)
{
	static int	counter = 0;
	int			len;
	int			path_nr;
	int			added;

	path_nr = 0;
	added = 0;
	len = 0;
	while (path_nr < map->path_qty)
	{
		len = 0;
		while (map->path[path_nr][len] > 0
			&& map->rooms[map->path[path_nr][len]] != NULL
			&& len < 101)
			len++;
		if (map->path[path_nr][0] > 0 && len < 101 && counter < len)
			added += add_room(map, path_nr, len, map->path[path_nr][len - 1]);
		path_nr++;
	}
	if (added > 0)
	{
		counter++;
		create_paths2(map);
	}
}

static void	create_paths1(t_map *map)
{
	int		i;
	int		conn;

	i = 0;
	map->rooms[map->start]->path_id = 1;
	sort_connections2(map, map->rooms[map->start]);
	map->path = (int**)ft_memalloc(sizeof(int*) * 102);
	if (map->path == NULL)
		exit(ft_printf("error: paths were not allocated\n"));
	while (i < map->path_qty)
	{
		conn = map->rooms[map->start]->in_out[i];
		map->path[i] = (int*)ft_memalloc(sizeof(int) * 102);
		if (map->path[i] == NULL)
			exit(ft_printf("error: path %d was not allocated\n", i));
		map->path[i][0] = conn;
		map->rooms[conn]->path_id = map->path[i][0];
		i++;
	}
	create_paths2(map);
}

void		overlaying_paths(t_map *map)
{
	assign_distance3a(map, map->start, 0);
	assign_distance3b(map, map->stop, 0);
	while (map->rooms[map->start]->in_out[map->path_qty] != 0)
		map->path_qty++;
	create_paths1(map);
	clean_and_sort1(map, &(map->path), (int[]){0, 0});
	assign_paths(map, 0, (int[]){0, 0, 0}, 999.0f);
}
