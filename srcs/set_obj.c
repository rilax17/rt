/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_obj.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyguel <nyguel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/16 19:26:00 by nyguel            #+#    #+#             */
/*   Updated: 2014/02/16 19:26:01 by nyguel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <stdlib.h>

void		ft_set_li(float c[3], int col[3], t_obj *obj)
{
	int		i;

	i = obj->nb_o[0];
	if (i < MAX_OBJ)
	{
		obj->nb_o[0] = i;
		obj->li[i].c[0] = c[0];
		obj->li[i].c[1] = c[1];
		obj->li[i].c[2] = c[2];
		obj->li[i].col[0] = col[0];
		obj->li[i].col[1] = col[1];
		obj->li[i].col[2] = col[2];
	}
	obj->refl[0 * MAX_OBJ + i] = 0;
	obj->tran[0 * MAX_OBJ + i] = 0;
	obj->nb_o[0] = i + 1;
}

void		ft_set_sph(float c[3], float r, int col[3], t_obj *obj)
{
	int		i;

	i = obj->nb_o[1];
	if (i < MAX_OBJ)
	{
		obj->sph[i].r = r;
		obj->sph[i].c[0] = c[0];
		obj->sph[i].c[1] = c[1];
		obj->sph[i].c[2] = c[2];
		obj->sph[i].col[0] = col[0];
		obj->sph[i].col[1] = col[1];
		obj->sph[i].col[2] = col[2];
	}
	obj->refl[1 * MAX_OBJ + i] = 0;
	obj->tran[1 * MAX_OBJ + i] = 0;
	obj->ind[1 * MAX_OBJ + i] = 5;
	obj->nb_o[1] = i + 1;
}


void		ft_set_pl(float c[3], float d, int col[3], t_obj *obj)
{
	int		i;

	i = obj->nb_o[2];
	if (i < MAX_OBJ)
	{
		obj->pl[i].a = c[0];
		obj->pl[i].b = c[1];
		obj->pl[i].c = c[2];
		obj->pl[i].d = d;
		obj->pl[i].col[0] = col[0];
		obj->pl[i].col[1] = col[1];
		obj->pl[i].col[2] = col[2];
	}
	obj->refl[2 * MAX_OBJ + i] = 0;
	obj->tran[2 * MAX_OBJ + i] = 0;
	obj->nb_o[2] = i + 1;
}

void		ft_set_cy(float cv[2][3], float r, int col[3], t_obj *obj)
{
	int		i;
	float	*tmp;

	i = obj->nb_o[3];
	if (i < MAX_OBJ)
	{
		tmp = (float *)malloc(sizeof(float) * 3);
		obj->cy[i].c[0] = cv[0][0];
		obj->cy[i].c[1] = cv[0][1];
		obj->cy[i].c[2] = cv[0][2];
		tmp[0] = cv[1][0];
		tmp[1] = cv[1][1];
		tmp[2] = cv[1][2];
		tmp = ft_norm_vect(tmp);
		obj->cy[i].v[0] = tmp[0];
		obj->cy[i].v[1] = tmp[1];
		obj->cy[i].v[2] = tmp[2];
		free(tmp);
		obj->cy[i].r = r;
		obj->cy[i].col[0] = col[0];
		obj->cy[i].col[1] = col[1];
		obj->cy[i].col[2] = col[2];
		obj->cy[i].mat = ft_fill_mat(obj->cy[i].v);
		obj->cy[i].min = -100;
		obj->cy[i].max = 150;
	}
	obj->refl[3 * MAX_OBJ + i] = 0;
	obj->tran[3 * MAX_OBJ + i] = 0;
	obj->ind[3 * MAX_OBJ + i] = 1.2;
	obj->nb_o[3] = i + 1;
}

void		ft_set_co(float cv[2][3], float a, int col[3], t_obj *obj)
{
	int		i;
	float	*tmp;

	i = obj->nb_o[4];
	if (i < MAX_OBJ)
	{
		tmp = (float *)malloc(sizeof(float) * 3);
		obj->co[i].c[0] = cv[0][0];
		obj->co[i].c[1] = cv[0][1];
		obj->co[i].c[2] = cv[0][2];
		tmp[0] = cv[1][0];
		tmp[1] = cv[1][1];
		tmp[2] = cv[1][2];
		tmp = ft_norm_vect(tmp);
		obj->co[i].v[0] = tmp[0];
		obj->co[i].v[1] = tmp[1];
		obj->co[i].v[2] = tmp[2];
		free(tmp);
		obj->co[i].alph = a;
		obj->co[i].col[0] = col[0];
		obj->co[i].col[1] = col[1];
		obj->co[i].col[2] = col[2];
		obj->co[i].mat = ft_fill_mat(obj->co[i].v);
		obj->co[i].min = -80;
		obj->co[i].max = 120;
	}
	obj->refl[4 * MAX_OBJ + i] = 0;
	obj->tran[4 * MAX_OBJ + i] = 0;
	obj->ind[4 * MAX_OBJ + i] = 0.6;
	obj->nb_o[4] = i + 1;
}
