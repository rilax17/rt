/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shade.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyguel <nyguel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/12 17:59:59 by nyguel            #+#    #+#             */
/*   Updated: 2014/02/12 18:00:01 by nyguel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <stdlib.h>
#include <math.h>

void		ft_shade(t_ray *ray, t_obj *obj, t_ray *tmp, int i)
{
	float	*refl;
	float	*v;

	v = ft_intxvect(-1, ray->v);
	ray->d_li[i] = tmp->d;
	refl = ft_refl(tmp->v, ray->norm);
	ray->li_cosd[i] = (ft_prod_scal(tmp->v, ray->norm));
	ray->li_coss[i] = ft_prod_scal(v, refl);
	free(refl);
	free(v);
	(void)obj;
}

float		ft_prod_scal(float *v1, float *v2)
{
	float	ret;

	ret = v1[0] * v2[0];
	ret = ret + v1[1] * v2[1];
	ret = ret + v1[2] * v2[2];
	return (ret);
}

float		*ft_refl(float v[3], float n[3])
{
	float	*refl;
	float	prod;

	prod = ft_prod_scal(n, v);
	refl = ft_intxvect(2 * prod, n);
	refl[0] = refl[0] - v[0];
	refl[1] = refl[1] - v[1];
	refl[2] = refl[2] - v[2];
	refl = ft_norm_vect(refl);
	return (refl);
}

