/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_get.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evilsbol <evilsbol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/21 13:52:12 by evilsbol          #+#    #+#             */
/*   Updated: 2014/03/21 13:54:22 by evilsbol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	rt_get_cam(int fd, t_dt *dt)
{
	char	*line;
	float	pos[3];
	float	dir[3];

	line = NULL;
	rt_init_float(pos, 3);
	rt_init_float(dir, 3);
	while (get_next_line(fd, &line) > 0 && ft_count(line, '}') == 0)
	{
		if (ft_strstr(line, "pos:"))
			rt_get_float(line, pos, 3);
		if (ft_strstr(line, "dir:"))
			rt_get_float(line, dir, 3);
		else
			continue;
	}
	rt_set_cam(pos, dir, dt);
	int i = -1;
	while (++i < 3)
		printf("cam: pos[%d]: %f|dir[%d]: %f\n", i, dt->cam_pos[i], i, dt->dir[i]);
}

void	rt_get_sph(int fd, t_obj *obj)
{
	char		*line;
	float		pos[3];
	int			col[3];
	float		rad[1];

	line = NULL;
	rt_init_float(pos, 3);
	rt_init_int(col, 3);
	while (get_next_line(fd, &line) > 0 && ft_count(line, '}') == 0)
	{
		if (ft_strstr(line, "pos"))
			rt_get_float(line, pos, 3);
		if (ft_strstr(line, "radius"))
			rt_get_float(line, rad, 1);
		if (ft_strstr(line, "color:"))
			rt_get_int(line, col, 3);
	}
	rt_set_sph(pos, rad, col, obj);
	int i = -1;
	while (++i < 3)
		printf("sphere: pos[%d]: %f|col[%d]: %d\n", i, obj->sph[i].c[i], i, obj->sph[i].col[i]);
}

// what is pos_v?
void	rt_get_cyl(int fd, t_obj *obj)
{
	char		*line;
	float		posv[2][3];
	int			col[3];
	float		rad[1];

	line = NULL;
	rt_init_float(posv[0], 3);
	rt_init_float(posv[1], 3);
	rt_init_int(col, 3);
	while (get_next_line(fd, &line) > 0 && ft_count(line, '}') == 0)
	{
		if (ft_strstr(line, "pos:"))
			//rt_get_float(line, pos, 3);
		if (ft_strstr(line, "radius"))
			rt_get_float(line, rad, 1);
		if (ft_strstr(line, "color"))
			rt_get_int(line, col, 3);
	}
	rt_set_cyl(posv, rad, col, obj);
	int i = -1;
	while (++i < 3)
		printf("cyl: pos[%d]: %f|col[%d]: %d\n", i, obj->cy[i].c[i], i, obj->cy[i].col[i]);
}

void	rt_get_pln(int fd, t_obj *obj)
{
	char		*line;
	float		pos[3];
	int			col[3];
	float		dist[1];

	line = NULL;
	while (get_next_line(fd, &line) > 0 && ft_count(line, '}') == 0)
	{
		if (ft_strstr(line, "pos"))
			rt_get_float(line, pos, 3);
		if (ft_strstr(line, "dist"))
			rt_get_float(line, dist, 1);
		if (ft_strstr(line, "color"))
			rt_get_int(line, col, 3);
	}
	rt_set_pln(pos, dist, col, obj);
	int i = -1;
	while (++i < 3)
		printf("plane: dist[%d]: %f|col[%d]: %d\n", i, obj->pl[i].d, i, obj->pl[obj->nb_o[2]].col[i]);
}

void	rt_get_spt(int fd, t_obj *obj)
{
	char		*line;
	float		pos[3];
	int			col[3];

	line = NULL;
	rt_init_float(pos, 3);
	rt_init_int(col, 3);
	while (get_next_line(fd, &line) > 0 && ft_count(line, '}') == 0)
	{
		if (ft_strstr(line, "pos:"))
			rt_get_float(line, pos, 3);
		if (ft_strstr(line, "color"))
			rt_get_int(line, col, 3);
	}
	rt_set_spt(pos, col, obj);
	int i = -1;
	while (++i < 3)
		printf("spt: pos[%d]: %f|col[%d]: %f\n", i, obj->li[i].c[i], i, obj->li[i].col[i]);
}
