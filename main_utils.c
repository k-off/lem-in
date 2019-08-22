/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main_utils.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: pacovali <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/12 18:56:23 by pacovali      #+#    #+#                 */
/*   Updated: 2019/01/23 17:53:36 by pacovali      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	free_str_arr(char **s, char ***arr, int flag)
{
	int			i;

	if ((flag == 1 || flag == 2) && *s != 0)
	{
		free(*s);
		*s = 0;
	}
	if ((flag == 0 || flag == 2) && arr != 0 && *arr != 0)
	{
		i = 0;
		while (arr[0][i])
		{
			free(arr[0][i]);
			i++;
		}
		free(*arr);
		*arr = 0;
	}
}

int		hash(char *s)
{
	unsigned	res;
	char		c;
	int			i;

	i = 0;
	res = 0;
	if (!s || ft_strlen(s) < 1 || ft_strlen(s) > 4)
		exit(ft_printf("error: bad string passed into hash function\n"));
	while (s[i] && i < 4)
	{
		c = s[i];
		if (ft_isdigit(c))
			c -= 48;
		else if (ft_isupper(c))
			c -= 55;
		else if (ft_islower(c))
			c -= 61;
		else
			c = 62;
		res <<= 5;
		res ^= c;
		i++;
	}
	return (res);
}

int		sort_connections(t_map *map, t_room *room)
{
	int			i[2];
	int			tmp;

	i[0] = 0;
	i[1] = 0;
	while (i[0] < 100 && room->in_out[i[0] + 1] > 0)
	{
		if (map->rooms[room->in_out[i[0] + 1]]->dist
			< map->rooms[room->in_out[i[0]]]->dist)
		{
			tmp = room->in_out[i[0] + 1];
			room->in_out[i[0] + 1] = room->in_out[i[0]];
			room->in_out[i[0]] = tmp;
			i[1]++;
		}
		i[0]++;
	}
	if (i[1] > 0)
		sort_connections(map, room);
	return (i[0] + 1);
}

int		sort_connections2(t_map *map, t_room *room)
{
	int			i[2];
	int			tmp;

	i[0] = 0;
	i[1] = 0;
	if (room == NULL)
		return (0);
	while (i[0] + 1 < 100 && room->in_out[i[0] + 1] > 0)
	{
		if (room->in_out[i[0]] < 2097151
			&& map->rooms[room->in_out[i[0]]] != NULL
			&& map->rooms[room->in_out[i[0] + 1]] != NULL
			&& map->rooms[room->in_out[i[0] + 1]]->dist2
			< map->rooms[room->in_out[i[0]]]->dist2)
		{
			tmp = room->in_out[i[0] + 1];
			room->in_out[i[0] + 1] = room->in_out[i[0]];
			room->in_out[i[0]] = tmp;
			i[1]++;
		}
		i[0]++;
	}
	if (i[1] > 0)
		sort_connections2(map, room);
	return (i[0] + 1);
}
