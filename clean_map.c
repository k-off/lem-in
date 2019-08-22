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

static void	arrange_in_out(t_room *room)
{
	int		i[2];

	i[0] = 0;
	while (i[0] < 100 && room->in_out[i[0]] != 0)
		i[0]++;
	i[1] = i[0];
	while (i[1] < 100 && room->in_out[i[1]] == 0)
		i[1]++;
	if (i[1] < 100 && room->in_out[i[1]] > 0)
	{
		room->in_out[i[0]] = room->in_out[i[1]];
		room->in_out[i[1]] = 0;
		arrange_in_out(room);
	}
}

static int	clean_room(t_map *map, int room)
{
	int		i[2];

	i[0] = 0;
	while (i[0] < 100 && map->rooms[room]->in_out[0]
		&& map->rooms[map->rooms[room]->in_out[0]]->in_out[i[0]] > 0)
	{
		if (map->rooms[map->rooms[room]->in_out[0]]->in_out[i[0]] == room)
		{
			map->rooms[map->rooms[room]->in_out[0]]->in_out[i[0]] = 0;
			arrange_in_out(map->rooms[map->rooms[room]->in_out[0]]);
			map->room_del++;
			break ;
		}
		i[0]++;
	}
	if (i[0] >= 100 || map->rooms[room]->in_out[0] == 0)
		exit(ft_printf("error: no solution\n"));
	if (map->rooms[room]->in_out != 0)
		free(map->rooms[room]->in_out);
	if (map->rooms[room]->name != 0)
		free(map->rooms[room]->name);
	free(map->rooms[room]);
	map->rooms[room] = 0;
	return (1);
}

void		clean_map(t_map *map)
{
	int		i[4];

	i[0] = 0;
	i[3] = 0;
	while (i[0] < 2097151)
	{
		if (map->rooms[i[0]] && map->rooms[i[0]]->in_out)
		{
			i[1] = 0;
			i[2] = 0;
			while (i[1] < 100)
			{
				if (map->rooms[i[0]]->in_out[i[1]] != 0)
					i[2]++;
				i[1]++;
			}
			if (i[2] < 2)
				i[3] += clean_room(map, i[0]);
		}
		i[0]++;
	}
	if (i[3] > 0)
		clean_map(map);
}
