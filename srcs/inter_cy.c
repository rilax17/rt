/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter_cy.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyguel <nyguel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/16 18:56:04 by nyguel            #+#    #+#             */
/*   Updated: 2014/02/16 18:56:05 by nyguel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <stdlib.h>
#include <math.h>

static float	ft_dist_cy(t_cy cy, t_ray *ray, int i, float **v_o);
static float	ft_check_end(t_cy cy, t_ray *ray, float a[5], float **v_o);
static void		ft_inter_end1(t_cy cy, float z[2], float d[4], float **v_o);
static float	ft_inter_end2(t_ray *ray, float d[5], float a[5]);
float			ft_inside_cy(t_ray *ray, float d[5], float ret, int i);

void			ft_inter_cy(t_ray *ray, t_obj *obj)
{
	int			i;
	float		tmp;
	float		**v_o;

	i = 0;
	tmp = ray->d;
	while (i < obj->nb_o[3])
	{
		v_o = (float **)malloc(sizeof(float *) * 3);
		tmp = ft_dist_cy(obj->cy[i], ray, i, v_o);
		ray->o_d[3 * MAX_OBJ + i] = tmp;
		if (tmp < ray->d && tmp >= 0)
		{
			ray->d = tmp;
			ray->o_nb = 3 * MAX_OBJ + i;
		}
		free(v_o[0]);
		free(v_o[1]);
		free(v_o[2]);
		free(v_o);
		i++;
	}
}

static float	ft_dist_cy(t_cy cy, t_ray *ray, int i, float **v_o)
{
	float		a[5];
	float		ret;

	a[4] = i;
	v_o[0] = ft_vect_base(ray->v, cy.mat);
	v_o[2] = ft_vec_min(ray->O, cy.c);
	v_o[1] = ft_vect_base(v_o[2], cy.mat);
	a[0] = v_o[0][1] * v_o[0][1] + v_o[0][2] * v_o[0][2];
	a[1] = 2 * (v_o[0][1] * v_o[1][1] + v_o[0][2] * v_o[1][2]);
	a[2] = v_o[1][1] * v_o[1][1] + v_o[1][2] * v_o[1][2] - cy.r * cy.r;
	a[3] = a[1] * a[1] - 4 * a[0] * a[2];
	if (a[3] < 0)
		return (D_MAX);
	ret = ft_check_end(cy, ray, a, v_o);
	if (ray->opt_f == 1 && sqrtf(a[3]) < ray->delta && ret < D_MAX && ret >= 0)
		ray->d_d[3 * MAX_OBJ + i] = 1;
	else if (ret < D_MAX)
		ray->d_d[3 * MAX_OBJ + i] = 0;
	return (ret);
}

static float	ft_check_end(t_cy cy, t_ray *ray, float a[5], float **v_o)
{
	float		d[5];
	float		x[2];
	int			i;

	d[4] = a[4];
	ray->norm_end[(int)a[4]] = 0;
	d[0] = (-a[1] - sqrtf(a[3])) / (2 * a[0]);
	d[1] = (-a[1] + sqrtf(a[3])) / (2 * a[0]);
	x[0] = v_o[1][0] + d[0] * v_o[0][0];
	x[1] = v_o[1][0] + d[1] * v_o[0][0];
	i = -1;
	ft_inter_end1(cy, x, d, v_o);
	while (++i < 2)
	{
		if ((x[i] > cy.max || x[i] < cy.min) && d[i] >= 0)
			d[i] = D_MAX;
	}
	return (ft_inter_end2(ray, d, a));
}

static float	ft_inter_end2(t_ray *ray, float d[5], float a[5])
{
	int			i;
	float		ret;

	i = -1;
	ret = D_MAX + 1;
	while (++i < 4)
	{
		if (d[i] >= 0 && d[i] < ret && d[i] != D_MAX)
			ret = d[i];
	}
	if (d[2] == ret)
		ray->norm_end[(int)d[4]] = -1;
	else if (d[3] == ret)
		ray->norm_end[(int)d[4]] = 1;
	if (ret >= 0)
	{
		i = -1;
		while (++i < 4)
		{
			if (d[i] != ret && fabs(ret - d[i]) < ray->delta)
				a[3] = 0.001;
		}
	}
	return (ft_inside_cy(ray, d, ret, (int)a[4]));
}

static void		ft_inter_end1(t_cy cy, float x[2], float d[4], float **v_o)
{
	if (((cy.min < x[0] && cy.min > x[1]) || (cy.min < x[1] && cy.min > x[0])))
		d[2] = ((cy.min - v_o[1][0]) / v_o[0][0]);
	else
		d[2] = D_MAX;
	if (((cy.max > x[0] && cy.max < x[1]) || (cy.max > x[1] && cy.max < x[0])))
		d[3] = ((cy.max - v_o[1][0]) / v_o[0][0]);
	else
		d[3] = D_MAX;
}
