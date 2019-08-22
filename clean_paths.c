/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   clean_and_sort.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: pacovali <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/12 18:56:23 by pacovali      #+#    #+#                 */
/*   Updated: 2019/01/23 17:53:36 by pacovali      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static void	change_paths(t_map *map, int ***path, int path_nr)
{
	int		i;
	int		tmp;

	tmp = map->path_len[path_nr];
	map->path_len[path_nr] = map->path_len[path_nr + 1];
	map->path_len[path_nr + 1] = tmp;
	i = 0;
	while (i < 102)
	{
		tmp = path[0][path_nr][i];
		path[0][path_nr][i] = path[0][path_nr + 1][i];
		path[0][path_nr + 1][i] = tmp;
		i++;
	}
}

static void	clean_and_sort3(t_map *map, int ***path)
{
	int		found;
	int		i;

	found = 0;
	i = 0;
	while (path[0][i][0] > 0 && i < map->path_qty - 1)
	{
		if (map->path_len[i] > map->path_len[i + 1]
			&& map->path_len[i + 1] != 0)
		{
			found++;
			change_paths(map, path, i);
		}
		i++;
	}
	if (found > 0)
		clean_and_sort3(map, path);
}

static void	clean_and_sort2(t_map *map, int ***path, int i[])
{
	int		found;

	found = 0;
	while (map->path_len[i[0]] != 0 && i[0] < map->path_qty)
		i[0]++;
	i[1] = i[0];
	while (map->path_len[i[1]] == 0 && i[1] < map->path_qty)
		i[1]++;
	if (i[0] < map->path_qty && i[1] < map->path_qty && i[0] < i[1])
	{
		map->path_len[i[0]] = map->path_len[i[1]];
		map->path_len[i[1]] = 0;
		while (path[0][i[1]][i[2]] != 0 && i[2] < 102)
		{
			path[0][i[0]][i[2]] = path[0][i[1]][i[2]];
			path[0][i[1]][i[2]] = 0;
			i[2]++;
		}
		clean_and_sort2(map, path, (int[]){0, 0, 0});
	}
	clean_and_sort3(map, path);
}

void		clean_and_sort1(t_map *map, int ***path, int i[])
{
	map->path_len = (int*)ft_memalloc(sizeof(int) * map->path_qty + 1);
	while (i[0] < map->path_qty)
	{
		i[1] = 0;
		if (path[0][i[0]][0] > 0)
		{
			while (i[1] < 102)
			{
				path[0][i[0]][i[1]] = 0;
				i[1]++;
				map->path_len[i[0]] = 0;
			}
		}
		else if (path[0][i[0]][0] < 0)
		{
			path[0][i[0]][0] = -path[0][i[0]][0];
			while (path[0][i[0]][map->path_len[i[0]]] != 0
				&& map->path_len[i[0]] < 102)
				map->path_len[i[0]]++;
		}
		i[0]++;
	}
	clean_and_sort2(map, &(map->path), (int[]){0, 0, 0});
}
