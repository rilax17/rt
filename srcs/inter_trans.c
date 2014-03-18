/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter_trans.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyguel <nyguel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/15 19:47:09 by nyguel            #+#    #+#             */
/*   Updated: 2014/03/15 19:47:10 by nyguel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <stdlib.h>
#include <math.h>

static float	ft_get_inds(t_ray *ray, t_obj *obj);

void			ft_init_trans(t_ray *ray, t_ray *tran, t_obj *obj)
{
	float	k;
	float	n;
	float	scal;
	float	*tmp;
	float	*tmp2;

	tmp2 = ft_intxvect(-1, ray->norm);
	ft_li_pos(tmp2, tran);
	free(tmp2);
	ray->tran = tran;
	n = ft_get_inds(ray, obj);
	scal = ft_prod_scal(ray->v, ray->norm);
	if (1 + n * n * (scal * scal - 1) > 0)
		k = n * scal - sqrt((1 + n * n * (scal * scal - 1)));
	else
		k = n * scal;
	tmp = ft_intxvect(k, ray->norm);
	tmp[0] = n * ray->v[0] + tmp[0];
	tmp[1] = n * ray->v[1] + tmp[1];
	tmp[2] = n * ray->v[2] + tmp[2];
	tmp = ft_norm_vect(tmp);
	tran->v[0] = tmp[0];
	tran->v[1] = tmp[1];
	tran->v[2] = tmp[2];
	free(tmp);
}

static float	ft_get_inds(t_ray *ray, t_obj *obj)
{
	float	ind1;
	float	ind2;

	if (ray->ins == 1)
	{
		ind1 = obj->ind[ray->o_nb];
		ind2 = obj->ind_amb;
		if (ray->dneg < 0)
			ind2 = obj->ind[ray->oneg_nb];
	}
	else
	{
		ind2 = obj->ind[ray->o_nb];
		ind1 = obj->ind_amb;
		if (ray->dneg < 0)
			ind2 = obj->ind[ray->oneg_nb];
	}
	return (ind2 / ind1);
}
