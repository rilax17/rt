/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyguel <nyguel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/16 19:14:10 by nyguel            #+#    #+#             */
/*   Updated: 2014/02/16 19:14:13 by nyguel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <math.h>
#include <stdlib.h>

static void			ft_view_x(t_env *env, int key);
static void			ft_view_z(t_env *env, int key);
static void			ft_view_mipl(t_env *env, int key);
static void			ft_change_view(t_env **env, int key);

int					ft_loop(int key, t_env **env)
{
	if (key == ESC)
	{
		ft_clear(*env);
		exit(0);
	}
	if (key == LE || key == RI || key == ENT || key == UP || key == DO
			|| key == PL || key == MI)
		ft_change_view(env, key);
	return (0);
}

static void			ft_change_view(t_env **env, int key)
{
	if (key == LE || key == RI || key == ENT)
		ft_view_x(*env, key);
	if (key == UP || key == DO)
		ft_view_z(*env, key);
	if (key == PL || key == MI)
		ft_view_mipl(*env, key);
}

static void			ft_view_mipl(t_env *env, int key)
{
	float			*tmp;
	float			zoom;

	if (key == PL && env->dt->zoom > 30)
		zoom = 0.9;
	else if (key == MI && env->dt->zoom < 10000)
		zoom = 1.1;
	else
		zoom = 1;
	env->dt->opt_f = 1;
	env->dt->zoom = env->dt->zoom * zoom;
	tmp = ft_intxvect(zoom, env->dt->cam_pos);
	env->dt->cam_pos[0] = tmp[0];
	env->dt->cam_pos[1] = tmp[1];
	env->dt->cam_pos[2] = tmp[2];
	free(tmp);
	ft_ray_cast(env->dt, env->obj);
}

static void			ft_view_z(t_env *env, int key)
{
	static float	ang_z = 0;
	float			ang_prev;
	float			rat;

	env->dt->opt_f = 1;
	ang_prev = ang_z;
	if (key == UP)
		ang_z = ang_z + INC_A;
	if (key == DO)
		ang_z = ang_z - INC_A;
	if (ang_z >= PI / 2)
		ang_z = PI / 2 - INC_A;
	if (ang_z <= -PI / 2)
		ang_z = -PI / 2 + INC_A;
	rat = cos(ang_z) / cos(ang_prev);
	env->dt->cam_pos[2] = env->dt->zoom * sin(ang_z);
	env->dt->cam_pos[0] = env->dt->cam_pos[0] * rat;
	env->dt->cam_pos[1] = env->dt->cam_pos[1] * rat;
	ft_ray_cast(env->dt, env->obj);
}


static void			ft_view_x(t_env *env, int key)
{
	static float	ang_x = -PI;

	if (key == RI || key == LE)
	{
		env->dt->opt_f = 1;
		if (key == LE)
			ang_x = ang_x + INC_A;
		if (key == RI)
			ang_x = ang_x - INC_A;
		if (ang_x > 2 * PI)
			ang_x = ang_x - 2 * PI;
		if (ang_x < 0)
			ang_x = ang_x + 2 * PI;
		env->dt->cam_pos[0] = env->dt->zoom * sin(ang_x);
		env->dt->cam_pos[1] = env->dt->zoom * cos(ang_x);
	}
	if (key == ENT)
	{
		env->dt->opt_f = 0;
	}
	ft_ray_cast(env->dt, env->obj);
}
