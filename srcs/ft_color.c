/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_color.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyguel <nyguel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/12 19:39:55 by nyguel            #+#    #+#             */
/*   Updated: 2014/02/12 19:39:57 by nyguel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <stdlib.h>
#include <math.h>

void			ft_get_color_obj(t_ray *ray, t_obj *obj, t_col *col);
void			ft_calc_li(t_ray *ray, t_obj *obj, t_col *col);
static void		ft_init_col(t_ray *ray, t_col *col);
static void		ft_calc_col(t_col *col, t_ray *ray);
static void		ft_rec_col(t_ray *ray, t_obj *obj);
void			ft_get_dir_li(t_ray *ray, t_obj *obj, t_col *col);
void			ft_max_col(float col[3]);

void			ft_get_color(t_ray *ray, t_obj *obj)
{
	t_col		*col;

	col = (t_col *)malloc(sizeof(t_col));
	ft_init_col(ray, col);
	if (ray->d < D_MAX)
	{
		ft_get_color_obj(ray, obj, col);
		if (ray->opt_f == 0)
		{
			col->amb[0] = col->obj[0] * obj->amb[0];
			col->amb[1] = col->obj[1] * obj->amb[1];
			col->amb[2] = col->obj[2] * obj->amb[2];
			ft_calc_li(ray, obj, col);
			ft_calc_col(col, ray);
			if (ray->refl != NULL)
				ft_get_color(ray->refl, obj);
			if (ray->tran != NULL)
				ft_get_color(ray->tran, obj);
		}
		ft_rec_col(ray, obj);
	}
	ft_get_dir_li(ray, obj, col);
	free(col);
}

static void		ft_rec_col(t_ray *ray, t_obj *obj)
{
	if (ray->refl != NULL)
	{
		ray->col[0] = ray->refl->col[0] * obj->refl[ray->o_nb]
			+ (1 - obj->refl[ray->o_nb]) * ray->col[0];
		ray->col[1] = ray->refl->col[1] * obj->refl[ray->o_nb]
			+ (1 - obj->refl[ray->o_nb]) * ray->col[1];
		ray->col[2] = ray->refl->col[2] * obj->refl[ray->o_nb]
			+ (1 - obj->refl[ray->o_nb]) * ray->col[2];
		free(ray->refl);
		ray->refl = NULL;
	}
	if (ray->tran != NULL)
	{
		ray->col[0] = ray->tran->col[0] * obj->tran[ray->o_nb]
			+ (1 - obj->tran[ray->o_nb]) * ray->col[0];
		ray->col[1] = ray->tran->col[1] * obj->tran[ray->o_nb]
			+ (1 - obj->tran[ray->o_nb]) * ray->col[1];
		ray->col[2] = ray->tran->col[2] * obj->tran[ray->o_nb]
			+ (1 - obj->tran[ray->o_nb]) * ray->col[2];
		free(ray->tran);
		ray->tran = NULL;
	}
}

static void		ft_init_col(t_ray *ray, t_col *col)
{
	col->dir_li[0] = 0;
	col->dir_li[1] = 0;
	col->dir_li[2] = 0;
	col->obj[0] = 0;
	col->obj[1] = 0;
	col->obj[2] = 0;
	ray->col[0] = 0;
	ray->col[1] = 0;
	ray->col[2] = 0;
	col->sh[0][0] = 0;
	col->sh[0][1] = 0;
	col->sh[0][2] = 0;
	col->sh[1][0] = 0;
	col->sh[1][1] = 0;
	col->sh[1][2] = 0;
	col->amb[0] = 0;
	col->amb[1] = 0;
	col->amb[2] = 0;
}

static void		ft_calc_col(t_col *col, t_ray *ray)
{
	col->obj[0] = col->amb[0] + col->sh[0][0] + col->sh[1][0];
	col->obj[1] = col->amb[1] + col->sh[0][1] + col->sh[1][1];
	col->obj[2] = col->amb[2] + col->sh[0][2] + col->sh[1][2];
	ft_max_col(col->obj);
	ray->col[0] = (int)col->obj[0];
	ray->col[1] = (int)col->obj[1];
	ray->col[2] = (int)col->obj[2];
}