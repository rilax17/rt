/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_threads.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyguel <nyguel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/15 20:00:19 by nyguel            #+#    #+#             */
/*   Updated: 2014/03/15 23:14:46 by nyguel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "rt.h"
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <mlx.h>

void			ft_set_param(t_dt *dt);
void				ft_join_th(t_env *env, t_dt dt[4]);
void				ft_init_th(t_dt *dt_i, t_dt dt[4]);
void				*ft_rc_th1(void *env);
void				*ft_rc_th2(void *env);
void				*ft_rc_th3(void *env);
void				*ft_rc_th4(void *env);

void			ft_mlx_add_col(t_dt *dt, t_ray *ray);
void			ft_init_ray(t_ray *ray, t_dt *dt);
void			ft_get_color(t_ray *ray, t_obj *obj);
void			ft_inter(t_ray *ray, t_obj *obj);

void				ft_rc_th(t_env *env)
{
	pthread_t		th[4];
	t_dt			dt[4];
	t_dt			*save;

	ft_set_param(env->dt);
	save = env->dt;
	ft_init_th(env->dt, dt);
	env->dt = &dt[0];
	if (pthread_create(&th[0], NULL, ft_rc_th1, env))
		write(1, "error thread\n", 13);
	env->dt = &dt[1];
	if (pthread_create(&th[1], NULL, ft_rc_th2, env))
		write(1, "error thread\n", 13);
	env->dt = &dt[2];
	if (pthread_create(&th[2], NULL, ft_rc_th3, env))
		write(1, "error thread\n", 13);
	env->dt = &dt[3];
	if (pthread_create(&th[3], NULL, ft_rc_th4, env))
		write(1, "error thread\n", 13);
	pthread_join(th[0], NULL);
	pthread_join(th[1], NULL);
	pthread_join(th[2], NULL);
	pthread_join(th[3], NULL);
	env->dt = save;
	ft_join_th(env, dt);
}

void				ft_join_th(t_env *env, t_dt dt[4])
{
	int				i;

	i = -1;
	(void)dt;
	while (++i < X_MAX * Y_MAX)
	{
		if (i < X_MAX * Y_MAX / 4)
			env->dt->img_c[i] = dt[0].img_c[i];
		if (i > X_MAX * Y_MAX / 4 && i < X_MAX * Y_MAX * 2 / 4)
			env->dt->img_c[i] = dt[1].img_c[i];
		if (i > X_MAX * Y_MAX * 2 / 4 && i < X_MAX * Y_MAX * 3 / 4)
			env->dt->img_c[i] = dt[2].img_c[i];
		if (i > X_MAX * Y_MAX * 3 / 4)
			env->dt->img_c[i] = dt[3].img_c[i];
	}
	mlx_put_image_to_window(env->dt->conn, env->dt->win, env->dt->img, 0, 0);
}

void				ft_init_th(t_dt *dt_i, t_dt dt[4])
{
	int			i;

	i = -1;
	while (++i < 4)
	{
		dt[i].img_c = (char *)malloc(sizeof(char) * X_MAX * Y_MAX / 4);
		dt[i].s_line = dt->s_line;
		dt[i].bpp = dt->bpp;
		dt[i].cam_pos[0] = dt_i->cam_pos[0];
		dt[i].cam_pos[1] = dt_i->cam_pos[1];
		dt[i].cam_pos[2] = dt_i->cam_pos[2];
		dt[i].opt_f = dt_i->opt_f;
		dt[i].delta = dt_i->delta;
		ft_set_param(&dt[i]);
	}
}

void				*ft_rc_th1(void *env)
{
	t_ray			*ray;
	int				pix[2];
	t_env			*tmp;

	tmp = (t_env *)env;
	pix[1] = 0;
	while (pix[1] < Y_MAX / 4)
	{
		pix[0] = 0;
		while (pix[0] < X_MAX)
		{
			ray = (t_ray *)malloc(sizeof(t_ray));
			ray->pix[1] = pix[1];
			ray->pix[0] = pix[0];
			ft_init_ray(ray, tmp->dt);
			ft_inter(ray, tmp->obj);
			ft_get_color(ray, tmp->obj);
			ft_mlx_add_col(tmp->dt, ray);
			pix[0] = pix[0] + 1;
			free(ray);
		}
		pix[1] = pix[1] + 1;
	}
	return (NULL);
}

void				*ft_rc_th2(void *env)
{
	t_ray			*ray;
	int				pix[2];
	t_env			*tmp;

	tmp = (t_env *)env;
	pix[1] = Y_MAX / 4;
	while (pix[1] < 2 * Y_MAX / 4)
	{
		pix[0] = 0;
		while (pix[0] < X_MAX)
		{
			ray = (t_ray *)malloc(sizeof(t_ray));
			ray->pix[1] = pix[1];
			ray->pix[0] = pix[0];
			ft_init_ray(ray, tmp->dt);
			ft_inter(ray, tmp->obj);
			ft_get_color(ray, tmp->obj);
			ft_mlx_add_col(tmp->dt, ray);
			pix[0] = pix[0] + 1;
			free(ray);
		}
		pix[1] = pix[1] + 1;
	}
	return (NULL);
}

void				*ft_rc_th3(void *env)
{
	t_ray			*ray;
	int				pix[2];
	t_env			*tmp;

	tmp = (t_env *)env;
	pix[1] = 2 * Y_MAX / 4;
	while (pix[1] < 3 * Y_MAX / 4)
	{
		pix[0] = 0;
		while (pix[0] < X_MAX)
		{
			ray = (t_ray *)malloc(sizeof(t_ray));
			ray->pix[1] = pix[1];
			ray->pix[0] = pix[0];
			ft_init_ray(ray, tmp->dt);
			ft_inter(ray, tmp->obj);
			ft_get_color(ray, tmp->obj);
			ft_mlx_add_col(tmp->dt, ray);
			pix[0] = pix[0] + 1;
			free(ray);
		}
		pix[1] = pix[1] + 1;
	}
	return (NULL);
}

void				*ft_rc_th4(void *env)
{
	t_ray			*ray;
	int				pix[2];
	t_env			*tmp;

	tmp = (t_env *)env;
	pix[1] = 3 * Y_MAX / 4;
	while (pix[1] < Y_MAX)
	{
		pix[0] = 0;
		while (pix[0] < X_MAX)
		{
			ray = (t_ray *)malloc(sizeof(t_ray));
			ray->pix[1] = pix[1];
			ray->pix[0] = pix[0];
			ft_init_ray(ray, tmp->dt);
			ft_inter(ray, tmp->obj);
			ft_get_color(ray, tmp->obj);
			ft_mlx_add_col(tmp->dt, ray);
			pix[0] = pix[0] + 1;
			free(ray);
		}
		pix[1] = pix[1] + 1;
	}
	return (NULL);
}
