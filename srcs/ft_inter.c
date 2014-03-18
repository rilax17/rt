/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_inter.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyguel <nyguel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/07 18:29:45 by nyguel            #+#    #+#             */
/*   Updated: 2014/02/12 16:04:58 by nyguel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <stdlib.h>

void	ft_inter_sph(t_ray *ray, t_obj *obj);
void	ft_inter_pl(t_ray *ray, t_obj *obj);
void	ft_inter_cy(t_ray *ray, t_obj *obj);
void	ft_inter_co(t_ray *ray, t_obj *obj);
void	ft_init_reflex(t_ray *ray, t_ray *ref);
void	ft_init_trans(t_ray *ray, t_ray *tran, t_obj *obj);
void	ft_inter_li(t_ray *ray, t_obj *obj);
void	ft_inter_li_d(t_ray *ray, t_obj *obj);

void	ft_inter(t_ray *ray, t_obj *obj)
{
	t_ray	*refl;
	t_ray	*trans;

	ft_inter_obj(ray, obj);
	if (ray->d < D_MAX && ray->opt_f == 0)
	{
		ft_inter_li(ray, obj);
		if (ray->rec < REC_MAX && obj->refl[ray->o_nb] != 0)
		{
			refl = (t_ray *)malloc(sizeof(t_ray));
			ft_init_rec(ray, refl);
			ft_init_reflex(ray, refl);
			ft_inter(refl, obj);
		}
		if (ray->rec < REC_MAX && obj->tran[ray->o_nb] != 0)
		{
			trans = (t_ray *)malloc(sizeof(t_ray));
			ft_init_rec(ray, trans);
			ft_init_trans(ray, trans, obj);
			ft_inter(trans, obj);
		}
	}
}

void	ft_inter_obj(t_ray *ray, t_obj *obj)
{
	ft_inter_sph(ray, obj);
	ft_inter_pl(ray, obj);
	ft_inter_cy(ray, obj);
	ft_inter_co(ray, obj);
	if (ray->opt_f == 0)
		ft_inter_li_d(ray, obj);
}

void	ft_init_rec(t_ray *in, t_ray *out)
{
	out->rec = in->rec + 1;
	out->opt_f = 0;
	out->d = D_MAX;
	out->dneg = 0;
	out->tran = NULL;
	out->refl = NULL;
	out->O[0] = in->v[0] * in->d + in->O[0];
	out->O[1] = in->v[1] * in->d + in->O[1];
	out->O[2] = in->v[2] * in->d + in->O[2];
}

void	ft_init_reflex(t_ray *ray, t_ray *ref)
{
	float	v[3];
	float	*tmp;

	ft_li_pos(ray->norm, ref);
	ray->refl = ref;
	v[0] = -ray->v[0];
	v[1] = -ray->v[1];
	v[2] = -ray->v[2];
	tmp = ft_refl(v, ray->norm);
	tmp = ft_norm_vect(tmp);
	ref->v[0] = tmp[0];
	ref->v[1] = tmp[1];
	ref->v[2] = tmp[2];
	free(tmp);
}
