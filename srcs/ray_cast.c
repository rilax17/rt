/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyguel <nyguel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/07 18:24:29 by nyguel            #+#    #+#             */
/*   Updated: 2014/02/12 16:04:30 by nyguel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <stdlib.h>
#include <math.h>
#include <mlx.h>

void			ft_set_param(t_dt *dt);
void			ft_get_color(t_ray *ray, t_obj *obj);
void			ft_mlx_add_col(t_dt *dt, t_ray *ray);
void			ft_inter(t_ray *ray, t_obj *obj);
void			ft_init_ray(t_ray *ray, t_dt *dt);
static float	*ft_calc_vect(float **tmp);
static void		ft_get_vector(t_dt *dt, t_ray *ray);
static void		ft_change_base(t_dt *dt, t_ray *ray);

void			ft_ray_cast(t_dt *dt, t_obj *obj)
{
	t_ray		*ray;
	int			pix[2];

	pix[1] = 0;
	ft_set_param(dt);
	while (pix[1] < Y_MAX)
	{
		pix[0] = 0;
		while (pix[0] < X_MAX)
		{
			ray = (t_ray *)malloc(sizeof(t_ray));
			ray->pix[1] = pix[1];
			ray->pix[0] = pix[0];
			ft_init_ray(ray, dt);
			ft_inter(ray, obj);
			ft_get_color(ray, obj);
			ft_mlx_add_col(dt, ray);
			pix[0] = pix[0] + 1;
			free(ray);
		}
		pix[1] = pix[1] + 1;
		mlx_put_image_to_window(dt->conn, dt->win, dt->img, 0, 0);
	}
}

static void		ft_get_vector(t_dt *dt, t_ray *ray)
{
	float		X;
	float		Y;
	float		**tmp;
	float		del;
	float		*tmp2;

	tmp = (float **)malloc(sizeof(float *) * 3);
	del = 2 / (float)X_MAX;
	tmp[0] = ft_intxvect(dt->foc, dt->axes[0]);
	X = del * ((float)X_MAX / 2 - ((float)ray->pix[0] + 0.5));
	Y = del * ((float)Y_MAX / 2 - ((float)ray->pix[1] + 0.5));
	tmp[1] = ft_intxvect(X, dt->axes[1]);
	tmp[2] = ft_intxvect(Y, dt->axes[2]);
	tmp2 = ft_calc_vect(tmp);
	tmp2 = ft_norm_vect(tmp2);
	ray->v[0] = tmp2[0];
	ray->v[1] = tmp2[1];
	ray->v[2] = tmp2[2];
	free(tmp[0]);
	free(tmp[1]);
	free(tmp[2]);
	free(tmp);
	free(tmp2);
}

static float	*ft_calc_vect(float **tmp)
{
	int			i;
	int			j;
	float		*ret;

	ret = (float *)malloc(sizeof(float) * 3);
	ret[0] = 0;
	ret[1] = 0;
	ret[2] = 0;
	i = 0;
	while (i < 3)
	{
		j = 0;
		while (j < 3)
		{
			ret[j] = ret[j] + tmp[i][j];
			j++;
		}
		i++;
	}
	return (ret);
}

void			ft_init_ray(t_ray *ray, t_dt *dt)
{
	ray->opt_f = dt->opt_f;
	ray->delta = dt->delta;
	ft_get_vector(dt, ray);
	ft_change_base(dt, ray);
	ray->rec = 1;
	ray->d = D_MAX;
	ray->dneg = 0;
	ray->refl = NULL;
	ray->tran = NULL;
	ray->O[0] = dt->cam_pos[0];
	ray->O[1] = dt->cam_pos[1];
	ray->O[2] = dt->cam_pos[2];
}

static void		ft_change_base(t_dt *dt, t_ray *ray)
{
	float		v2[3];

	v2[0] = ray->v[0] * dt->dir[0] + ray->v[1] * dt->mat_v[0] + ray->v[2]
		* dt->mat_w[0];
	v2[1] = ray->v[0] * dt->dir[1] + ray->v[1] * dt->mat_v[1] + ray->v[2]
		* dt->mat_w[1];
	v2[2] = ray->v[0] * dt->dir[2] + ray->v[1] * dt->mat_v[2] + ray->v[2]
		* dt->mat_w[2];
	ray->v[0] = v2[0];
	ray->v[1] = v2[1];
	ray->v[2] = v2[2];
}

