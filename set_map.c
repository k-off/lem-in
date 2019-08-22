/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   set_map.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: pacovali <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/12 18:56:23 by pacovali      #+#    #+#                 */
/*   Updated: 2019/01/23 17:53:36 by pacovali      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static void	initial_setup(t_map **map, int fd)
{
	char	*s;
	int		i;

	map[0] = (t_map*)ft_memalloc(sizeof(t_map) * 1);
	if (!map)
		exit(ft_printf("error: map not allocated\n"));
	map[0]->rooms = (t_room**)ft_memalloc(sizeof(t_room*) * 2097152);
	if (get_next_line(fd, &s) < 1)
		exit(ft_printf("error: file couldn't be read\n"));
	if (!ft_str_is_numeric(s))
		exit(ft_printf("error: first line must be number of ants\n"));
	map[0]->ant_qty = ft_atoi(s);
	if (map[0]->ant_qty < 1)
		exit(ft_printf("error: no ants - very funny\n"));
	map[0]->ants = (t_ant*)ft_memalloc(sizeof(t_ant) * map[0]->ant_qty + 1);
	i = 0;
	while (i < map[0]->ant_qty)
	{
		(&map[0]->ants[i])->nr = i + 1;
		i++;
	}
	map[0]->start = -2;
	map[0]->stop = -2;
	ft_printf("%s\n", s);
	free_str_arr(&s, NULL, 1);
}

static void	set_room(t_map *map, char *s)
{
	char	**tmp;
	int		i;
	int		id;

	map->room_qty++;
	tmp = ft_strsplit(s, ' ');
	i = 0;
	while (tmp && tmp[i])
		i++;
	if (i != 3 || !tmp || ft_strlen(tmp[0]) < 1 || ft_strlen(tmp[1]) < 1
		|| ft_strlen(tmp[2]) < 1 || ft_strlen(tmp[0]) > 4 || tmp[0][0] == 'L')
		exit(ft_printf("error: room declaration is wrong\n"));
	id = hash(tmp[0]);
	if (map->start == -1)
		map->start = id;
	if (map->stop == -1)
		map->stop = id;
	map->rooms[id] = (t_room*)ft_memalloc(sizeof(t_room));
	map->rooms[id]->id_r = id;
	map->rooms[id]->name = strdup(tmp[0]);
	map->rooms[id]->x = ft_atoi(tmp[1]);
	map->rooms[id]->y = ft_atoi(tmp[2]);
	if (map->rooms[id]->x < 0 || map->rooms[id]->y < 0)
		exit(ft_printf("error: negative room coordinates\n"));
	free_str_arr(NULL, &tmp, 0);
}

static void	set_conn_value(int **arr, int id)
{
	int		i;

	i = 0;
	while (arr[0][i] > 0 && i < 100)
		i++;
	if (i >= 100)
		exit(ft_printf("error: to many connections to a single room"));
	arr[0][i] = id;
}

static void	set_connection(t_map *map, char *s)
{
	char	**tmp;
	int		id[2];
	int		i;

	tmp = 0;
	tmp = ft_strsplit(s, '-');
	i = 0;
	while (tmp && tmp[i])
		i++;
	if (i != 2 || !tmp || ft_strlen(tmp[0]) < 1 || ft_strlen(tmp[1]) < 1
		|| ft_strlen(tmp[0]) > 4 || ft_strlen(tmp[1]) > 4)
		exit(ft_printf("error: connection wrong declared\n"));
	id[0] = hash(tmp[0]);
	id[1] = hash(tmp[1]);
	if (!map->rooms[id[0]] || !map->rooms[id[1]])
		exit(ft_printf("error: room doesn't exist, can't assign connection\n"));
	if (!map->rooms[id[0]]->in_out)
		map->rooms[id[0]]->in_out = (int*)ft_memalloc(sizeof(int) * 100 + 1);
	if (!map->rooms[id[1]]->in_out)
		map->rooms[id[1]]->in_out = (int*)ft_memalloc(sizeof(int) * 100 + 1);
	set_conn_value(&map->rooms[id[0]]->in_out, id[1]);
	set_conn_value(&map->rooms[id[1]]->in_out, id[0]);
	free_str_arr(NULL, &tmp, 0);
}

t_map		*set_map(int fd)
{
	t_map	*map;
	char	*s;

	initial_setup(&map, fd);
	s = 0;
	while (get_next_line(fd, &s) || ft_strlen(s) > 0)
	{
		if (ft_strstr(s, "##start") && map->start == -2)
			map->start = -1;
		else if (ft_strstr(s, "##end") && map->stop == -2)
			map->stop = -1;
		else if (s[0] != '#' && strchr(s, ' '))
			set_room(map, s);
		else if (s[0] != '#' && strchr(s, '-'))
			set_connection(map, s);
		ft_printf("%s\n", s);
		free_str_arr(&s, NULL, 1);
	}
	if (s)
		ft_printf("%s\n", s);
	if (s)
		free_str_arr(&s, NULL, 1);
	if (map->stop < 0 || map->start < 0 || map->ant_qty < 1)
		exit(ft_printf("error: map wrong declared\n"));
	return (map);
}
