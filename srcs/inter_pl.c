/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter_pl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyguel <nyguel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/07 18:33:16 by nyguel            #+#    #+#             */
/*   Updated: 2014/02/07 18:33:20 by nyguel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <math.h>
#include <stdlib.h>

static float	ft_dist_pl(t_pl pl, float O[3], float vect[3]);

void			ft_inter_pl(t_ray *ray, t_obj *obj)
{
	int			i;
	float		tmp;

	i = 0;
	tmp = ray->d;
	while (i < obj->nb_o[2])
	{
		tmp = ft_dist_pl(obj->pl[i], ray->O, ray->v);
		ray->o_d[2 * MAX_OBJ + i] = tmp;
		ray->d_d[2 * MAX_OBJ + i] = 0;
		if (tmp < ray->d && tmp >= 0)
		{
			ray->d = tmp;
			ray->o_nb = 2 * MAX_OBJ + i;
		}
		i++;
	}
}


static float	ft_dist_pl(t_pl pl, float O[3], float vect[3])
{
	float		d;
	float		a;
	float		b;

	a = pl.a * O[0] + pl.b * O[1] + pl.c * O[2] + pl.d;
	b = pl.a * vect[0] + pl.b * vect[1] + pl.c * vect[2];
	if (b == 0)
		return (D_MAX);
	d = -a / b;
	if (d < 0)
		return (D_MAX);
	return (d);
}

float			ft_dist_li(t_li li, t_ray *ray)
{
	float		*tmp;
	float		tmp2;

	tmp = ft_intxvect(ray->d, ray->v);
	tmp[0] = tmp[0] + ray->O[0];
	tmp[1] = tmp[1] + ray->O[2];
	tmp[2] = tmp[2] + ray->O[2];
	tmp2 = ft_dist_pts(li.c, tmp);
	free(tmp);
	return (tmp2);
}

float			ft_dist_pts(float *a, float *b)
{
	float		ret;
	float		c;
	float		d;
	float		e;

	c = (a[0] - b[0]) * (a[0] - b[0]);
	d = (a[1] - b[1]) * (a[1] - b[1]);
	e = (a[2] - b[2]) * (a[2] - b[2]);
	ret = sqrtf(c + d + e);
	return (ret);
}
