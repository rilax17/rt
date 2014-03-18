/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyguel <nyguel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/07 18:17:32 by nyguel            #+#    #+#             */
/*   Updated: 2014/03/15 23:14:21 by nyguel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <stdlib.h>
#include <mlx.h>

int				ft_loop(int key, t_env **env);
void			ft_set_obj(t_obj *obj);
static int		ft_set_mlx(t_dt *dt);
static int		ft_expose(t_env *env);
void				ft_rc_th(t_env *env);

int				main(void)
{
	t_env		*env;

	if ((env = (t_env *)malloc(sizeof(t_env))) == NULL)
		return (-1);
	if ((env->dt = (t_dt *)malloc(sizeof(t_dt))) == NULL)
		return (-1);
	if ((env->obj = (t_obj *)malloc(sizeof(t_obj))) == NULL)
		return (-1);
	ft_set_mlx(env->dt);
	env->dt->zoom = ZOOM;
	env->dt->cam_pos[0] = 0;
	env->dt->cam_pos[1] = -ZOOM;
	env->dt->cam_pos[2] = 0;
	env->dt->opt_f = 0;
	env->dt->delta = 10;
	ft_set_obj(env->obj);
	ft_ray_cast(env->dt, env->obj);
//	ft_rc_th(env);
	mlx_key_hook(env->dt->win, &ft_loop, &env);
	mlx_expose_hook(env->dt->win, ft_expose, env);
	mlx_loop(env->dt->conn);
	return (0);
}

void			ft_clear(t_env *env)
{
	mlx_destroy_window(env->dt->conn, env->dt->win);
}

void			ft_mlx_add_col(t_dt *dt, t_ray *ray)
{
	dt->img_c[(ray->pix[1] * dt->s_line) + (ray->pix[0] * (dt->bpp / 8))]
		= ray->col[2];
	dt->img_c[(ray->pix[1] * dt->s_line) + (ray->pix[0] * (dt->bpp / 8)) + 1]
		= ray->col[1];
	dt->img_c[(ray->pix[1] * dt->s_line) + (ray->pix[0] * (dt->bpp / 8)) + 2]
		= ray->col[0];
}

static int		ft_set_mlx(t_dt *dt)
{
	if ((dt->conn = mlx_init()) == NULL)
		return (-1);
	if ((dt->win = mlx_new_window(dt->conn, X_MAX, Y_MAX, "Rt")) == NULL)
		return (-1);
	if ((dt->img = mlx_new_image(dt->conn, X_MAX, Y_MAX)) == NULL)
		return (-1);
	dt->img_c = mlx_get_data_addr(dt->img, &(dt->bpp), &(dt->s_line),
			&(dt->endian));
	return (1);
}

static int		ft_expose(t_env *env)
{
	mlx_put_image_to_window(env->dt->conn, env->dt->win, env->dt->img, 0, 0);
	return (0);
}

