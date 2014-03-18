/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_li.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyguel <nyguel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/15 19:42:11 by nyguel            #+#    #+#             */
/*   Updated: 2014/03/15 19:42:13 by nyguel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <math.h>

static void		ft_get_shade_d(t_ray *ray, t_obj *obj, t_col *col);
static void		ft_get_shade_s(t_ray *ray, t_obj *obj, t_col *col);
void			ft_max_col(float col[3]);

void			ft_calc_li(t_ray *ray, t_obj *obj, t_col *col)
{
	ft_get_shade_s(ray, obj, col);
	ft_get_shade_d(ray, obj, col);
}

void			ft_get_dir_li(t_ray *ray, t_obj *obj, t_col *col)
{
	int			i;
	float		k;

	i = -1;
	while (++i < obj->nb_o[0])
	{
		if (ray->li_cos[i] != 0)
		{
			k = pow(ray->li_cos[i], 20 + ray->d_dir_li[i]);
			col->dir_li[0] = col->dir_li[0] + k * obj->li[i].col[0];
			col->dir_li[1] = col->dir_li[1] + k * obj->li[i].col[1];
			col->dir_li[2] = col->dir_li[2] + k * obj->li[i].col[2];
			ft_max_col(col->dir_li);
		}
	}
	col->dir_li[0] = ray->col[0] + (int)col->dir_li[0];
	col->dir_li[1] = ray->col[1] + (int)col->dir_li[1];
	col->dir_li[2] = ray->col[2] + (int)col->dir_li[2];
	ft_max_col(col->dir_li);
	ray->col[0] = (int)col->dir_li[0];
	ray->col[1] = (int)col->dir_li[1];
	ray->col[2] = (int)col->dir_li[2];
}

static void		ft_get_shade_d(t_ray *ray, t_obj *obj, t_col *col)
{
	int			i;
	float		coef;

	i = -1;
	while (++i < obj->nb_o[0])
	{
		if (ray->d_li[i] != D_MAX)
		{
			coef = 0.5 + 0.0001 * ray->d_li[i] + 0.00001 * pow(ray->d_li[i], 2);
			col->sh[0][0] = col->sh[0][0] + obj->k_d * ray->li_cosd[i]
				* obj->li[i].col[0] / coef;
			col->sh[0][1] = col->sh[0][1] + obj->k_d * ray->li_cosd[i]
				* obj->li[i].col[1] / coef;
			col->sh[0][2] = col->sh[0][2] + obj->k_d * ray->li_cosd[i]
				* obj->li[i].col[2] / coef;
		}
	}
	ft_max_col(col->sh[0]);
}

static void		ft_get_shade_s(t_ray *ray, t_obj *obj, t_col *col)
{
	int			i;
	float		coef;

	i = -1;
	while (++i < obj->nb_o[0])
	{
		if (ray->d_li[i] != D_MAX)
		{
			coef = 0.5 + 0.0001 * ray->d_li[i] + 0.00001 * pow(ray->d_li[i], 2);
			col->sh[1][0] = col->sh[1][0] + obj->k_s * pow(ray->li_coss[i],
					obj->alph) * obj->li[i].col[0] / coef;
			col->sh[1][1] = col->sh[1][1] + obj->k_s * pow(ray->li_coss[i],
					obj->alph) * obj->li[i].col[1] / coef;
			col->sh[1][2] = col->sh[1][2] + obj->k_s * pow(ray->li_coss[i],
					obj->alph) * obj->li[i].col[2] / coef;
		}
	}
	ft_max_col(col->sh[1]);
}

void			ft_max_col(float col[3])
{
	if (col[0] < 0)
		col[0] = 0;
	if (col[1] < 0)
		col[1] = 0;
	if (col[2] < 0)
		col[2] = 0;
	if (col[0] > 255)
		col[0] = 255;
	if (col[1] > 255)
		col[1] = 255;
	if (col[2] > 255)
		col[2] = 255;
}
