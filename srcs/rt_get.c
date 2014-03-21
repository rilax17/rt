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

	while (get_next_line(fd, &line) > 0 && ft_count(line, '}') == 0)
	{
		if (ft_strstr(line, "pos:"))
			rt_get_float(line, pos, 3);
		else if (ft_strstr(line, "dir:"))
			rt_get_float(line, dir, 3);
		else
			continue;
	}
	rt_set_cam(pos, dir, dt);
	int i = -1;
	while (++i < 3)
		printf("pos: %f | dir: %f\n", dt->cam_pos[i], dt->dir[i]);
}

void	rt_get_sph(int fd, t_obj *obj)
{
	(void)fd;
	(void)obj;
	ft_printf("sphere\n");
}

void	rt_get_cyl(int fd, t_obj *obj)
{
	(void)fd;
	(void)obj;
	ft_printf("cylindre\n");
}

void	rt_get_pln(int fd, t_obj *obj)
{
	(void)fd;
	(void)obj;
	ft_printf("plane\n");
}

void	rt_get_spt(int fd, t_obj *obj)
{
	(void)fd;
	(void)obj;
	ft_printf("spot\n");
}
