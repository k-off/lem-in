/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: pacovali <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/12 18:56:23 by pacovali      #+#    #+#                 */
/*   Updated: 2019/01/23 17:53:36 by pacovali      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	check_map(t_map *map)
{
	int		i;

	i = 0;
	while (map->rooms[map->start]->in_out
		&& map->rooms[map->start]->in_out[i] > 0)
		i++;
	if (i < 1)
		exit(ft_printf("error: no connections\n"));
	if (map->room_qty < 750 || map->ant_qty < 50)
		map->type = 1;
	else if (map->room_qty / (float)(map->room_del + map->room_qty) < 0.85)
		map->type = 2;
	else
		map->type = 3;
}

int		main(void)
{
	t_map	*map;
	int		fd;

	fd = 0;
	map = set_map(fd);
	clean_map(map);
	check_map(map);
	if (map->type == 1)
		distinct_paths(map);
	else if (map->type == 2)
		crossing_paths(map);
	else if (map->type == 3)
		overlaying_paths(map);
	return (0);
}
