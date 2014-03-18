/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter_li.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyguel <nyguel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/07 18:30:26 by nyguel            #+#    #+#             */
/*   Updated: 2014/02/12 16:06:16 by nyguel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <stdlib.h>

void			ft_shade(t_ray *ray, t_obj *obj, t_ray *tmp, int i);
static void		ft_init_vect_li(t_ray *ray_li, t_li li);
void			ft_normale(t_ray *ray, t_obj *obj, t_ray *tmp);

void			ft_inter_li(t_ray *ray, t_obj *obj)
{
	int			i;
	float		tmp2;
	t_ray		*tmp;

	tmp = (t_ray *)malloc(sizeof(t_ray));
	ft_init_rec(ray, tmp);
	ft_normale(ray, obj, tmp);
	ft_li_pos(ray->norm, tmp);
	i = 0;
	while (i < obj->nb_o[0])
	{
		tmp2 = ft_dist_pts(obj->li[i].c, tmp->O);
		if (tmp2 < D_MAX)
		{
			tmp->d = tmp2;
			ft_init_vect_li(tmp, obj->li[i]);
			ft_inter_obj(tmp, obj);
			if (tmp->d < tmp2)
				ray->d_li[i] = D_MAX;
			else
				ft_shade(ray, obj, tmp, i);
		}
		i++;
	}
	free(tmp);
}

void			ft_inter_li_d(t_ray *ray, t_obj *obj)
{
	int			i;
	float		scal;
	float		*tmp2;

	i = 0;
	while (i < obj->nb_o[0])
	{
		ray->li_cos[i] = 0;
		tmp2 = ft_vec_min(obj->li[i].c, ray->O);
		tmp2 = ft_norm_vect(tmp2);
		scal = ft_prod_scal(ray->v, tmp2);
		if (scal > 0)
		{
			ray->d_dir_li[i] = ft_dist_pts(obj->li[i].c, ray->O);
			ray->li_cos[i] = scal;
		}
		free(tmp2);
		i++;
	}
}

void			ft_li_pos(float *norm, t_ray *ray_li)
{
	float		eps;
	float		*tmp;

	eps = 0.1;
	tmp = (float *)malloc(sizeof(float) * 3);
	tmp[0] = eps * norm[0];
	tmp[1] = eps * norm[1];
	tmp[2] = eps * norm[2];
	ray_li->O[0] = ray_li->O[0] + tmp[0];
	ray_li->O[1] = ray_li->O[1] + tmp[1];
	ray_li->O[2] = ray_li->O[2] + tmp[2];
	free(tmp);
}

static void		ft_init_vect_li(t_ray *ray_li, t_li li)
{
	float		*tmp3;

	ray_li->opt_f = 1;
	tmp3 = (float *)malloc(sizeof(float) * 3);
	tmp3[0] = li.c[0] - ray_li->O[0];
	tmp3[1] = li.c[1] - ray_li->O[1];
	tmp3[2] = li.c[2] - ray_li->O[2];
	tmp3 = ft_norm_vect(tmp3);
	ray_li->v[0] = tmp3[0];
	ray_li->v[1] = tmp3[1];
	ray_li->v[2] = tmp3[2];
	free(tmp3);
}
