/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_normale.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyguel <nyguel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/07 18:31:49 by nyguel            #+#    #+#             */
/*   Updated: 2014/02/07 18:48:42 by nyguel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <stdlib.h>
#include <math.h>

static float	*ft_norm_sph(t_sph sph, t_ray *tmp);
static float	*ft_norm_pl(t_pl pl);
static float	*ft_norm_cy(t_cy cy, t_ray *tmp, int norm_end);
static float	*ft_norm_co(t_co co, t_ray *tmp, int norm_end);
float			*ft_sel_norm(float *norm, t_ray *ray);

void			ft_normale(t_ray *ray, t_obj *obj, t_ray *tmp)
{
	float		*tmp2;

	if (ray->o_nb / MAX_OBJ == 1)
		tmp2 = ft_norm_sph(obj->sph[ray->o_nb % MAX_OBJ], tmp);
	else if (ray->o_nb / MAX_OBJ == 2)
		tmp2 = ft_norm_pl(obj->pl[ray->o_nb % MAX_OBJ]);
	else if (ray->o_nb / MAX_OBJ == 3)
		tmp2 = ft_norm_cy(obj->cy[ray->o_nb % MAX_OBJ], tmp,
				ray->norm_end[ray->o_nb % MAX_OBJ]);
	else//if (ray->o_nb / MAX_OBJ == 4)
		tmp2 = ft_norm_co(obj->co[ray->o_nb % MAX_OBJ], tmp,
				ray->norm_end[ray->o_nb % MAX_OBJ + MAX_OBJ]);
	tmp2 = ft_sel_norm(tmp2, ray);
	ray->norm[0] = tmp2[0];
	ray->norm[1] = tmp2[1];
	ray->norm[2] = tmp2[2];
	free(tmp2);
}

static float	*ft_norm_sph(t_sph sph, t_ray *tmp)
{
	float		*norm;

	norm = (float *)malloc(sizeof(float) * 3);
	norm[0] = tmp->O[0] - sph.c[0];
	norm[1] = tmp->O[1] - sph.c[1];
	norm[2] = tmp->O[2] - sph.c[2];
	norm = ft_norm_vect(norm);
	return (norm);
}

static float	*ft_norm_cy(t_cy cy, t_ray *tmp, int norm_end)
{
	float		*norm;
	float		*h;
	float		*p;
	float		scal;

	if (norm_end == 1)
		return (ft_intxvect(1, cy.v));
	if (norm_end == -1)
		return (ft_intxvect(-1, cy.v));
	h = ft_vec_min(tmp->O, cy.c);
	scal = ft_prod_scal(h, cy.v);
	p = ft_intxvect(scal, cy.v);
	norm = ft_vec_min(h, p);
	norm = ft_norm_vect(norm);
	free(h);
	free(p);
	return (norm);
}

static float	*ft_norm_co(t_co co, t_ray *tmp, int norm_end)
{
	float		*norm;
	float		*h;
	float		*p;
	float		scal;
	int			neg;

	if (norm_end == 1)
		return (ft_intxvect(1, co.v));
	if (norm_end == -1)
		return (ft_intxvect(-1, co.v));
	h = ft_vec_min(tmp->O, co.c);
	scal = ft_prod_scal(h, co.v);
	neg = 1;
	if (scal > 0)
		neg = -1;
	p = ft_intxvect(scal, co.v);
	norm = ft_vec_min(h, p);
	norm = ft_norm_vect(norm);
	norm[0] = norm[0] + neg * fabs(tan(co.alph)) * co.v[0];
	norm[1] = norm[1] + neg * fabs(tan(co.alph)) * co.v[1];
	norm[2] = norm[2] + neg * fabs(tan(co.alph)) * co.v[2];
	norm = ft_norm_vect(norm);
	free(h);
	free(p);
	return (norm);
}

static float	*ft_norm_pl(t_pl pl)
{
	float		*norm;

	norm = (float *)malloc(sizeof(float) * 3);
	norm[0] = pl.a;
	norm[1] = pl.b;
	norm[2] = pl.c;
	norm = ft_norm_vect(norm);
	return (norm);
}
