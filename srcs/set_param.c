/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_param.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyguel <nyguel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/07 18:18:35 by nyguel            #+#    #+#             */
/*   Updated: 2014/02/07 18:46:34 by nyguel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <stdlib.h>
#include <math.h>

static void		ft_get_axes(t_dt *dt);
static void		ft_get_v(t_dt *dt);
static void		ft_get_w(t_dt *dt);

void			ft_set_param(t_dt *dt)
{
	float		*tmp;

	dt->foc = 1 / tan(PHI / 2);
	tmp = ft_intxvect(-1, dt->cam_pos);
	tmp = ft_norm_vect(tmp);
	dt->dir[0] = tmp[0];
	dt->dir[1] = tmp[1];
	dt->dir[2] = tmp[2];
	free(tmp);
	ft_get_axes(dt);
}

static void		ft_get_axes(t_dt *dt)
{
	dt->axes[0][0] = 1;
	dt->axes[0][1] = 0;
	dt->axes[0][2] = 0;
	dt->axes[1][0] = 0;
	dt->axes[1][1] = -1;
	dt->axes[1][2] = 0;
	dt->axes[2][0] = 0;
	dt->axes[2][1] = 0;
	dt->axes[2][2] = 1;
	ft_get_w(dt);
	ft_get_v(dt);
}

static void		ft_get_v(t_dt *dt)
{
	float		*tmp;

	tmp = ft_prod_vect(dt->dir, dt->mat_w);
	dt->mat_v[0] = tmp[0];
	dt->mat_v[1] = tmp[1];
	dt->mat_v[2] = tmp[2];
	free(tmp);
}

static void		ft_get_w(t_dt *dt)
{
	float		*tmp;
	float		scal;

	scal = ft_prod_scal(dt->dir, dt->axes[2]);
	tmp = ft_intxvect(scal, dt->dir);
	tmp[0] = dt->axes[2][0] - tmp[0];
	tmp[1] = dt->axes[2][1] - tmp[1];
	tmp[2] = dt->axes[2][2] - tmp[2];
	tmp = ft_norm_vect(tmp);
	dt->mat_w[0] = tmp[0];
	dt->mat_w[1] = tmp[1];
	dt->mat_w[2] = tmp[2];
	free(tmp);
}
