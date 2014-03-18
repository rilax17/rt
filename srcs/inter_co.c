
#include "rt.h"
#include <stdlib.h>
#include <math.h>

static float	ft_dist_co(t_co co, t_ray *ray, int i, float **v_o);
static float	ft_check_end(t_co co, t_ray *ray, float a[5], float **v_o);
static void		ft_inter_end1(t_co co, float d[4], float **v_o);
static float	ft_inter_end2(t_ray *ray, float d[5], float a[5]);
float			ft_inside_co(t_ray *ray, float d[5], float ret, int i);

void			ft_inter_co(t_ray *ray, t_obj *obj)
{
	int			i;
	float		tmp;
	float		**v_o;

	i = 0;
	tmp = ray->d;
	while (i < obj->nb_o[4])
	{
		v_o = (float **)malloc(sizeof(float *) * 3);
		tmp = ft_dist_co(obj->co[i], ray, i, v_o);
		ray->o_d[4 * MAX_OBJ + i] = tmp;
		if (tmp < ray->d && tmp >= 0)
		{
			ray->d = tmp;
			ray->o_nb = 4 * MAX_OBJ + i;
		}
		free(v_o[0]);
		free(v_o[1]);
		free(v_o[2]);
		free(v_o);
		i++;
	}
}

static float	ft_dist_co(t_co co, t_ray *ray, int i, float **v_o)
{
	float		a[5];
	float		ret;
	float		c_s[0];

	a[4] = i;
	c_s[0] = pow(cos(co.alph), 2);
	c_s[1] = pow(sin(co.alph), 2);
	v_o[0] = ft_vect_base(ray->v, co.mat);
	v_o[2] = ft_vec_min(ray->O, co.c);
	v_o[1] = ft_vect_base(v_o[2], co.mat);
	a[0] = c_s[0] * (v_o[0][1] * v_o[0][1] + v_o[0][2] * v_o[0][2])
		- v_o[0][0] * v_o[0][0] * c_s[1];
	a[1] = 2 * c_s[0] * (v_o[0][1] * v_o[1][1] + v_o[0][2] * v_o[1][2])
		- 2 * c_s[1] * v_o[0][0] * v_o[1][0];
	a[2] = c_s[0] * (v_o[1][1] * v_o[1][1] + v_o[1][2] * v_o[1][2])
		- c_s[1] * v_o[1][0] * v_o[1][0];
	a[3] = a[1] * a[1] - 4 * a[0] * a[2];
	if (a[3] < 0)
		return (D_MAX);
	ret = ft_check_end(co, ray, a, v_o);
	if (ray->opt_f == 1 && sqrtf(a[3]) < ray->delta && ret < D_MAX)
		ray->d_d[4 * MAX_OBJ + i] = 1;
	else if (ret < D_MAX)
		ray->d_d[4 * MAX_OBJ + i] = 0;
	return (ret);
}

static float	ft_check_end(t_co co, t_ray *ray, float a[5], float **v_o)
{
	float		d[5];
	float		x[2];
	int			i;

	d[4] = a[4];
	ray->norm_end[(int)a[4] + MAX_OBJ] = 0;
	d[0] = (-a[1] - sqrtf(a[3])) / (2 * a[0]);
	d[1] = (-a[1] + sqrtf(a[3])) / (2 * a[0]);
	x[0] = v_o[1][0] + d[0] * v_o[0][0];
	x[1] = v_o[1][0] + d[1] * v_o[0][0];
	ft_inter_end1(co, d, v_o);
	i = -1;
	while (++i < 2)
	{
		if ((x[i] > co.max || x[i] < co.min) && d[i] >= 0)
			d[i] = D_MAX;
	}
	return (ft_inter_end2(ray, d, a));
}

static float	ft_inter_end2(t_ray *ray, float d[5], float a[5])
{
	int			i;
	float		ret;

	i = -1;
	ret = D_MAX + 1;
	while (++i < 4)
	{
		if (d[i] >= 0 && d[i] < ret && d[i] != D_MAX)
			ret = d[i];
	}
	if (d[2] == ret)
		ray->norm_end[(int)d[4] + MAX_OBJ] = -1;
	else if (d[3] == ret)
		ray->norm_end[(int)d[4] + MAX_OBJ] = 1;
	if (ret >= 0)
	{
		i = -1;
		while (++i < 4)
		{
			if (d[i] != ret && fabs(ret - d[i]) < ray->delta)
				a[3] = 0.001;
		}
	}
	return (ft_inside_co(ray, d, ret, (int)a[4]));
}

static void		ft_inter_end1(t_co co, float d[4], float **v_o)
{
	d[2] = ((co.min - v_o[1][0]) / v_o[0][0]);
	if (sqrt(pow(v_o[1][1] + d[2] * v_o[0][1], 2) + pow(v_o[1][2] + d[2]
					* v_o[0][2], 2)) > fabs(co.min * tan(co.alph)))
		d[2] = D_MAX;
	d[3] = ((co.max - v_o[1][0]) / v_o[0][0]);
	if (sqrt(pow(v_o[1][1] + d[3] * v_o[0][1], 2) + pow(v_o[1][2] + d[3]
					* v_o[0][2], 2)) > fabs(co.max * tan(co.alph)))
		d[3] = D_MAX;
}