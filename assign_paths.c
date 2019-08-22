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

static int	path_len(int *path)
{
	int		i;

	i = 0;
	while (path[i] > 0)
		i++;
	return (i);
}

void		assign_paths(t_map *map, int tot_d, int n[], float prev)
{
	tot_d = path_len(map->path[n[0]]);
	while ((map->ant_qty + tot_d) / (n[0] + 1.0)
		< prev && map->path[n[0]][0] != 0)
	{
		n[0]++;
		prev = (map->ant_qty + tot_d) / (float)(n[0]);
		tot_d += path_len(map->path[n[0]]);
	}
	if (n[0] < 2 && map->type != 1)
		exit(ft_printf("error: paths not found\n"));
	if ((int)prev < prev)
		prev = (int)prev + 1;
	while (n[0] > 0 && n[2] < map->ant_qty)
	{
		n[0]--;
		n[1] = 0;
		while (path_len(map->path[n[0]]) + n[1] < prev && n[2] < map->ant_qty)
		{
			(&map->ants[n[2]])->rout = map->path[n[0]];
			n[1]++;
			n[2]++;
		}
	}
	run_many(map, map->ant_qty, 1, (int[]){0, 0});
}
