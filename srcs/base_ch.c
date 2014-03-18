/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base_ch.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyguel <nyguel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/16 18:58:20 by nyguel            #+#    #+#             */
/*   Updated: 2014/02/16 18:58:23 by nyguel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <stdlib.h>

float			**ft_inv_mat(float **mat);
static float	*ft_mat_z(float v[3], float axes[3][3]);

float			**ft_fill_mat(float v[3])
{
	float		axes[3][3];
	float		**mat;

	axes[0][0] = 1;
	axes[0][1] = 0;
	axes[0][2] = 0;
	axes[1][0] = 0;
	axes[1][1] = 1;
	axes[1][2] = 0;
	axes[2][0] = 0;
	axes[2][1] = 0;
	axes[2][2] = 1;
	mat = (float **)malloc(sizeof(float *) * 3);
	mat[0] = (float *)malloc(sizeof(float) * 3);
	mat[0][0] = v[0];
	mat[0][1] = v[1];
	mat[0][2] = v[2];
	mat[2] = ft_mat_z(v, axes);
	mat[1] = ft_prod_vect(mat[2], v);
	mat = ft_inv_mat(mat);
	return (mat);
}

float			**ft_inv_mat(float **mat)
{
	int			i;
	int			j;
	float		**ret;

	ret = (float **)malloc(sizeof(float *) * 3);
	i = 0;
	while (i < 3)
	{
		ret[i] = (float *)malloc(sizeof(float) * 3);
		j = 0;
		while (j < 3)
		{
			ret[i][j] = mat[j][i];
			j++;
		}
		i++;
	}
	free(mat[0]);
	free(mat[1]);
	free(mat[2]);
	free(mat);
	return (ret);
}

static float	*ft_mat_z(float v[3], float axes[3][3])
{
	float		*mat_z;
	float		scal;

	scal = ft_prod_scal(v, axes[2]);
	mat_z = ft_intxvect(scal, v);
	mat_z[0] = axes[2][0] - mat_z[0];
	mat_z[1] = axes[2][1] - mat_z[1];
	mat_z[2] = axes[2][2] - mat_z[2];
	if (mat_z[0] == 0 && mat_z[1] == 0 && mat_z[2] == 0)
	{
		mat_z[0] = axes[0][0];
		mat_z[1] = axes[0][1];
		mat_z[2] = axes[0][2];
	}
	mat_z = ft_norm_vect(mat_z);
	return (mat_z);
}

float			*ft_vect_base(float v[3], float **mat)
{
	float		ret[3];
	float		*tmp;

	tmp = (float *)malloc(sizeof(float) * 3);
	ret[0] = v[0] * mat[0][0] + v[1] * mat[1][0] + v[2] * mat[2][0];
	ret[1] = v[0] * mat[0][1] + v[1] * mat[1][1] + v[2] * mat[2][1];
	ret[2] = v[0] * mat[0][2] + v[1] * mat[1][2] + v[2] * mat[2][2];
	tmp[0] = ret[0];
	tmp[1] = ret[1];
	tmp[2] = ret[2];
	return (tmp);
}
