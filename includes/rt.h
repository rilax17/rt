/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyguel <nyguel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/07 18:17:52 by nyguel            #+#    #+#             */
/*   Updated: 2014/02/07 18:18:00 by nyguel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# include <stdio.h>
# include <fcntl.h>
# include "libprt.h"
# include "gnl.h"

# define PI 3.14159
# define PHI (PI / 4)
# define X_MAX 700
# define Y_MAX 600
# define D_MAX 20000
# define NB_OBJ 5
# define MAX_OBJ 7
# define REC_MAX 50
# define NB_OPT 2
# define K_A 20
# define K_D 30
# define K_S 50
# define ALPH 100
# define ESC 65307
# define UP 65362
# define LE 65361
# define RI 65363
# define DO 65364
# define ENT 65293
# define PL 65451
# define MI 65453
# define ZOOM 350
# define INC_A PI / 30

/*
** PROGRAM ERROR MESSAGES
*/
# define USAGE "wrong number of arguments.\nusage: ./rt <mapname>"

typedef struct		s_dt
{
	void			*conn;
	void			*win;
	void			*img;
	char			*img_c;
	int				bpp;
	int				s_line;
	int				endian;
	float			cam_pos[3];
	float			dir[3];
	float			mat_v[3];
	float			mat_w[3];
	float			axes[3][3];
	int				opt_f;
	float			foc;
	float			d;
	int				col;
	int				col_r;
	int				col_g;
	int				col_b;
	int				calc_opt[NB_OPT];
	float			delta;
	float			zoom;
}					t_dt;

typedef struct		s_sph
{
	float			r;
	float			c[3];
	int				col[3];
}					t_sph;

typedef struct		s_pl
{
	float			a;
	float			b;
	float			c;
	float			d;
	int				col[3];
}					t_pl;

typedef struct		s_li
{
	float			c[3];
	float			col[3];
}					t_li;

typedef struct		s_cy
{
	float			c[3];
	float			v[3];
	int				col[3];
	float			r;
	float			**mat;
	float			min;
	float			max;
}					t_cy;

typedef struct		s_co
{
	float			c[3];
	float			v[3];
	int				col[3];
	float			alph;
	float			**mat;
	float			mm[2];
	float			min;
	float			max;
}					t_co;

typedef struct		s_obj
{
	t_li			li[MAX_OBJ];
	t_sph			sph[MAX_OBJ];
	t_pl			pl[MAX_OBJ];
	t_cy			cy[MAX_OBJ];
	t_co			co[MAX_OBJ];
	int				nb_o[NB_OBJ];
	float			refl[MAX_OBJ * NB_OBJ];
	float			tran[MAX_OBJ * NB_OBJ];
	float			ind[MAX_OBJ * NB_OBJ];
	float			amb[3];
	float			k_a;
	float			k_d;
	float			k_s;
	int				alph;
	float			ind_amb;
}					t_obj;

typedef struct		s_ray
{
	int				pix[2];
	struct s_ray	*refl;
	struct s_ray	*tran;
	float			d;
	float			o_d[NB_OBJ * MAX_OBJ];
	float			o_dneg[NB_OBJ * MAX_OBJ];
	float			dneg;
	int				oneg_nb;
	int				ins;
	int				rec;
	int				o_nb;
	int				opt_f;
	float			d_d[NB_OBJ * MAX_OBJ];
	float			delta;
	float			v[3];
	float			O[3];
	float			li_cosd[MAX_OBJ];
	float			li_coss[MAX_OBJ];
	float			d_li[MAX_OBJ];
	float			li_cos[MAX_OBJ];
	float			d_dir_li[MAX_OBJ];
	float			norm[3];
	int				col[3];
	int				norm_end[2 * MAX_OBJ];
}					t_ray;

typedef struct		s_col
{
	float			obj[3];
	float			sh[2][3];
	float			amb[3];
	float			dir_li[3];
}					t_col;

typedef struct		s_env
{
	t_dt			*dt;
	t_obj			*obj;
}					t_env;

void	ft_ray_cast(t_dt *dt, t_obj *obj);
void	ft_inter_obj(t_ray *ray, t_obj *obj);

float	*ft_intxvect(float x, float vect[3]);
float	*ft_norm_vect(float *vect);
float	*ft_prod_vect(float u[3], float v[3]);
float	*ft_vec_min(float a[3], float b[3]);
float	ft_prod_scal(float *v1, float *v2);
float	*ft_refl(float v[3], float n[3]);

float	**ft_fill_mat(float v[3]);
float	*ft_vect_base(float v[3], float **mat);

void	ft_clear(t_env *env);
int		ft_get_next_inter(t_ray *ray, t_obj *obj);

void	ft_init_rec(t_ray *in, t_ray *out);
void	ft_li_pos(float *norm, t_ray *ray_li);
float	ft_dist_li(t_li li, t_ray *ray);
float	ft_dist_pts(float a[3], float b[3]);

/*
** get_data functions.
*/
void	rt_get_data(char *argv, t_env *env);
void	rt_set_cam(t_dt *dt);


#endif /* !RT_H */
