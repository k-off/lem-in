/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lemin.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: pacovali <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/12 18:56:23 by pacovali      #+#    #+#                 */
/*   Updated: 2019/01/23 17:53:36 by pacovali      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef __LEMIN_H
# define __LEMIN_H

# include "libft.h"

typedef struct		s_room
{
	int				id_r;
	int				reserved;
	int				dist;
	int				dist2;
	char			*name;
	int				ant;
	int				is_set;
	int				path_id;
	int				*in_out;
	int				x;
	int				y;
}					t_room;

typedef struct		s_ant
{
	int				nr;
	int				*rout;
	int				room_id;
}					t_ant;

typedef struct		s_map
{
	int				over;
	int				b_res;
	int				d_res;
	int				start;
	int				min_id;
	int				max_id;
	int				stop;
	t_room			**rooms;
	t_room			**rooms_s;
	int				room_qty;
	int				room_del;
	int				ant_qty;
	int				ant_set;
	t_ant			*ants;
	int				**path;
	int				*path_len;
	int				*path_ids;
	int				***x_path;
	int				***clean;
	int				path_qty;
	char			*output;
	int				type;
}					t_map;

void				assign_distance1(t_map *map, int room_id, int dist);
void				assign_distance2(t_map *map, int room_id, int dist);
void				assign_distance3a(t_map *map, int room_id, int dist);
void				assign_distance3b(t_map *map, int room_id, int dist);
void				assign_paths(t_map *map, int tot_d, int n[], float prev);
void				clean_and_sort1(t_map *map, int ***path, int i[]);
void				clean_map(t_map *map);
void				crossing_paths(t_map *map);
void				distinct_paths(t_map *map);
void				free_str_arr(char **s, char ***arr, int flag);
int					hash(char *s);
void				overlaying_paths(t_map *map);
void				run_one(t_map *map);
void				run_many(t_map *map, int qty, int fin, int i[]);
t_map				*set_map(int fd);
int					sort_connections(t_map *map, t_room *room);
int					sort_connections2(t_map *map, t_room *room);

#endif
