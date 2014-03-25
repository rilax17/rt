/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyguel <nyguel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/07 18:22:51 by nyguel            #+#    #+#             */
/*   Updated: 2014/02/08 00:13:26 by nyguel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <stdlib.h>

// void			rt_set_spt(float c[3], int col[3], t_obj *obj);
// void			rt_set_sph(float c[3], float r[1], int col[3], t_obj *obj);
// void			rt_set_pln(float c[3], float d, int col[3], t_obj *obj);
// void			rt_set_cyl(float cv[2][3], float r, int col[3], t_obj *obj);
void			rt_set_co(float cv[2][3], float r, int col[3], t_obj *obj);
static void		ft_set_obj_fact1(t_obj *obj);
static void		ft_set_obj_fact2(t_obj *obj);
static void		ft_set_obj_fact3(t_obj *obj);
static void		ft_set_obj_fact4(t_obj *obj);
static void		ft_set_obj_fact5(t_obj *obj);

void		ft_set_obj(t_obj *obj)
{
	obj->k_a = 0.2 / (255);
	obj->amb[0] = obj->k_a * 255;
	obj->amb[1] = obj->k_a * 255;
	obj->amb[2] = obj->k_a * 255;
	obj->k_d = 0.4;
	obj->k_s = 0.8;
	obj->alph = 100;
	obj->nb_o[0] = 0;
	obj->nb_o[1] = 0;
	obj->nb_o[2] = 0;
	obj->nb_o[3] = 0;
	obj->nb_o[4] = 0;
	obj->ind_amb = 1;
//	ft_set_obj_fact1(obj);
}

static void		ft_set_obj_fact1(t_obj *obj)
{
	float	c[3];
	int		col[3];

	c[0] = -150; c[1] = -300; c[2] = -150;
	col[0] = 255; col[1] = 255;	col[2] = 255;
	rt_set_spt(c, col, obj);
	c[0] = 150;	c[1] = -300; c[2] = 150;
	col[0] = 255; col[1] = 255; col[2] = 255;
	rt_set_spt(c, col, obj);
	ft_set_obj_fact2(obj);
}

static void		ft_set_obj_fact2(t_obj *obj)
{
	float	c[3];
	int		col[3];
	float	r[1];

	r[0] = 30;
	c[0] = -100; c[1] = 100; c[2] = 0;
	col[0] = 0;	col[1] = 127; col[2] = 0;
	rt_set_sph(c, r, col, obj);
	r[0] = 30;
	c[0] = 100; c[1] = 100;	c[2] = 0;
	col[0] = 40; col[1] = 127; col[2] = 100;
	rt_set_sph(c, r, col, obj);
	r[0] = 70;
	c[0] = 0; c[1] = -150; c[2] = 0;
	col[0] = 139; col[1] = 69; col[2] = 19;
	rt_set_sph(c, r, col, obj);
	r[0] = 10;
	c[0] = -40;	c[1] = 0; c[2] = 5;
	col[0] = 250; col[1] = 165;	col[2] = 0;
	rt_set_sph(c, r, col, obj);
//	obj->refl[1 * MAX_OBJ + 0] = 1;
	obj->tran[1 * MAX_OBJ + 2] = 1;
	obj->refl[1 * MAX_OBJ + 1] = 1;
	ft_set_obj_fact3(obj);
}

static void		ft_set_obj_fact3(t_obj *obj)
{
	float	c[3];
	int		col[3];
	float	d;

	c[0] = 0; c[1] = 0;	c[2] = 1;
	d = 200;
	col[0] = 185; col[1] = 42; col[2] = 42;
	//ft_set_pl(c, d, col, obj);
	c[0] = 0; c[1] = 0;	c[2] = 1; 
	d = -200;
	col[0] = 42; col[1] = 185; col[2] = 42;
	//ft_set_pl(c, d, col, obj);
	c[0] = 0; c[1] = 1;	c[2] = 0; 
	d = -500; 
	col[0] = 0; col[1] = 0;	col[2] = 139;
	//ft_set_pl(c, d, col, obj);
	c[0] = 0; c[1] = 1; c[2] = 0;
	d = 500;
	col[0] = 0;	col[1] = 0;	col[2] = 139;
	//ft_set_pl(c, d, col, obj);
	c[0] = 1; c[1] = 0;	c[2] = 0;
	d = 200;
	col[0] = 148; col[1] = 0; col[2] = 211;
	//ft_set_pl(c, d, col, obj);
	c[0] = 1; c[1] = 0;	c[2] = 0;
	d = -200;
	col[0] = 148; col[1] = 0; col[2] = 211;
	//ft_set_pl(c, d, col, obj);
	//obj->refl[2 * MAX_OBJ + 2] = 1;
	//ft_set_obj_fact4(obj);
}

static void		ft_set_obj_fact4(t_obj *obj)
{
/*	int		col[3];
	float	r[1];
	float	cv[2][3];

	cv[0][0] = -150;
	cv[0][1] = 250;
	cv[0][2] = 200;
	cv[1][0] = -1;
	cv[1][1] = 0;
	cv[1][2] = 1;
	col[0] = 89;
	col[1] = 197;
	col[2] = 146;
	r = 15;
	ft_set_cy(cv, r, col, obj);
	cv[0][0] = 100;
	cv[0][1] = -100;
	cv[0][2] = 60;
	cv[1][0] = 1;
	cv[1][1] = 1;
	cv[1][2] = 0;
	col[0] = 146;
	col[1] = 197;
	col[2] = 45;
	ft_set_cy(cv, r, col, obj);
*/	obj->tran[3 * MAX_OBJ + 1] = 1;
	ft_set_obj_fact5(obj);
}

static void		ft_set_obj_fact5(t_obj *obj)
{
	int		col[3];
	float	a;
	float	cv[2][3];

	cv[0][0] = 0; cv[0][1] = 0;	cv[0][2] = 0;
	cv[1][0] = 0; cv[1][1] = 0;	cv[1][2] = 1;
	col[0] = 89; col[1] = 197;	col[2] = 146;
	a = PI / 5;
	//ft_set_co(cv, a, col, obj);
/*	cv[0][0] = 90;
	cv[0][1] = 60;
	cv[0][2] = -100;
	cv[1][0] = 1;
	cv[1][1] = 0;
	cv[1][2] = -4;
	col[0] = 146;
	col[1] = 197;
	col[2] = 45;
	a = PI / 6;
	ft_set_co(cv, a, col, obj);
	obj->refl[4 * MAX_OBJ + 1] = 1;
	obj->tran[4 * MAX_OBJ + 0] = 0.8;
	obj->ind[4 * MAX_OBJ + 0] = 1;
*/
}
