/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   run_ants.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: pacovali <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/12 18:56:23 by pacovali      #+#    #+#                 */
/*   Updated: 2019/01/23 17:53:36 by pacovali      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static void	make_step(t_map *map, int i[], int not_first)
{
	if (not_first)
	{
		map->rooms[(&map->ants[i[0]])->rout[0]]->ant = 0;
		(&map->ants[i[0]])->rout++;
	}
	ft_printf("L%d-%s ", (&map->ants[i[0]])->nr,
		map->rooms[(&map->ants[i[0]])->rout[0]]->name);
	(&map->ants[i[0]])->room_id = (&map->ants[i[0]])->rout[0];
	map->rooms[(&map->ants[i[0]])->rout[0]]->ant = (&map->ants[i[0]])->nr;
}

void		run_many(t_map *map, int qty, int fin, int i[])
{
	while (fin)
	{
		i[0] = 0;
		fin = 0;
		while (i[0] < qty)
		{
			if ((&map->ants[i[0]])->room_id == 0
				&& map->rooms[(&map->ants[i[0]])->rout[0]]->ant == 0)
			{
				make_step(map, i, 0);
				fin++;
			}
			else if ((&map->ants[i[0]])->room_id != 0
			&& map->rooms[(&map->ants[i[0]])->rout[0]]->ant ==
			(&map->ants[i[0]])->nr && (&map->ants[i[0]])->rout[0] != map->stop)
			{
				make_step(map, i, 1);
				fin++;
			}
			i[0]++;
		}
		if (fin > 0)
			ft_printf("\n");
	}
}
