/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter_sph.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyguel <nyguel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/07 18:34:28 by nyguel            #+#    #+#             */
/*   Updated: 2014/02/07 18:34:29 by nyguel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <math.h>
#include <stdlib.h>

static float	ft_inside(t_ray *ray, float a[4], float ret, int i);
static float	ft_sph_b(float vect[3], float tmp[3]);
static float	ft_sph_c(float tmp[3], t_sph sph);
static float	ft_dist_sph(t_sph sph, t_ray *ray, int i);

void			ft_inter_sph(t_ray *ray, t_obj *obj)
{
	int			i;
	float		tmp;

	i = 0;
	tmp = ray->d;
	while (i < obj->nb_o[1])
	{
		ray->o_dneg[1 * MAX_OBJ + i] = -D_MAX;
		tmp = ft_dist_sph(obj->sph[i], ray, i);
		ray->o_d[1 * MAX_OBJ + i] = tmp;
		if (tmp < ray->d && tmp >= 0)
		{
			ray->d = tmp;
			ray->o_nb = 1 * MAX_OBJ + i;
		}
		i++;
	}
}

static float	ft_dist_sph(t_sph sph, t_ray *ray, int i)
{
	float		a[4];
	float		*tmp;
	float		ret;

	tmp = ft_vec_min(ray->O, sph.c);
	a[0] = ray->v[1] * ray->v[1] + ray->v[2] * ray->v[2]
	+ ray->v[0] * ray->v[0];
	a[1] = ft_sph_b(ray->v, tmp);
	a[2] = ft_sph_c(tmp, sph);
	free(tmp);
	a[3] = a[1] * a[1] - 4 * a[0] * a[2];
	ret = ((-a[1] - sqrtf(a[3])) / (2 * a[0]));
	if (a[3] < 0)
		return (D_MAX);
	if (ray->opt_f == 1 && sqrtf(a[3]) < ray->delta && ret >= 0)
		ray->d_d[1 * MAX_OBJ + i] = 1;
	else
		ray->d_d[1 * MAX_OBJ + i] = 0;
	return (ft_inside(ray, a, ret, i));
}

static float	ft_inside(t_ray *ray, float a[4], float ret, int i)
{
	float		ret2;

	ret2 = ((-a[1] + sqrtf(a[3])) / (2 * a[0]));
	if (ret < 0 && ret2 >= 0)
	{
		ray->o_dneg[1 * MAX_OBJ + i] = ret;
		if (ret > ray->dneg || ray->dneg == 0)
		{
			ray->dneg = ret;
			ray->oneg_nb = 1 * MAX_OBJ + i;
		}
		ret = ret2;
	}
	else
		ray->o_dneg[1 * MAX_OBJ + i] = -D_MAX;
	return (ret);
}

static float	ft_sph_c(float tmp[3], t_sph sph)
{
	float		ret;

	ret = tmp[0] * tmp[0] + tmp[1] * tmp[1] + tmp[2] * tmp[2] - sph.r * sph.r;
	return (ret);
}

static float	ft_sph_b(float vect[3], float tmp[3])
{
	return (2 * (vect[0] * tmp[0] + vect[1] * tmp[1] + vect[2] * tmp[2]));
}
