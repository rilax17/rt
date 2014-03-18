/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_color_obj.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyguel <nyguel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/15 20:09:01 by nyguel            #+#    #+#             */
/*   Updated: 2014/03/15 20:09:10 by nyguel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <stdlib.h>
#include <math.h>

static void		ft_get_color_sph(t_ray *ray, t_obj *obj, t_col *col);
static void		ft_get_color_cy(t_ray *ray, t_obj *obj, t_col *col);
static void		ft_get_color_co(t_ray *ray, t_obj *obj, t_col *col);
static void		ft_get_color_pl(t_ray *ray, t_obj *obj, t_col *col);

void			ft_get_color_obj(t_ray *ray, t_obj *obj, t_col *col)
{
	float	mul;

	if (ray->opt_f == 0)
	{
		if (ray->o_nb / MAX_OBJ == 1)
			ft_get_color_sph(ray, obj, col);
		if (ray->o_nb / MAX_OBJ == 2)
			ft_get_color_pl(ray, obj, col);
		if (ray->o_nb / MAX_OBJ == 3)
			ft_get_color_cy(ray, obj, col);
		if (ray->o_nb / MAX_OBJ == 4)
			ft_get_color_co(ray, obj, col);
	}
	else
	{
		if (ray->d_d[ray->o_nb] == 1 || ft_get_next_inter(ray, obj) == 1)
			mul = 2;
		else
			mul = 1;
		ray->col[0] = 255 / mul;
		ray->col[1] = 255 / mul;
		ray->col[2] = 255 / mul;
	}
}

static void		ft_get_color_sph(t_ray *ray, t_obj *obj, t_col *col)
{
	col->obj[0] = obj->sph[ray->o_nb % MAX_OBJ].col[0];
	col->obj[1] = obj->sph[ray->o_nb % MAX_OBJ].col[1];
	col->obj[2] = obj->sph[ray->o_nb % MAX_OBJ].col[2];
}

static void		ft_get_color_pl(t_ray *ray, t_obj *obj, t_col *col)
{
	col->obj[0] = obj->pl[ray->o_nb % MAX_OBJ].col[0];
	col->obj[1] = obj->pl[ray->o_nb % MAX_OBJ].col[1];
	col->obj[2] = obj->pl[ray->o_nb % MAX_OBJ].col[2];
}

static void		ft_get_color_cy(t_ray *ray, t_obj *obj, t_col *col)
{
	col->obj[0] = obj->cy[ray->o_nb % MAX_OBJ].col[0];
	col->obj[1] = obj->cy[ray->o_nb % MAX_OBJ].col[1];
	col->obj[2] = obj->cy[ray->o_nb % MAX_OBJ].col[2];
}

static void		ft_get_color_co(t_ray *ray, t_obj *obj, t_col *col)
{
	col->obj[0] = obj->co[ray->o_nb % MAX_OBJ].col[0];
	col->obj[1] = obj->co[ray->o_nb % MAX_OBJ].col[1];
	col->obj[2] = obj->co[ray->o_nb % MAX_OBJ].col[2];
}

