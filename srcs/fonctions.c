/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fonctions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyguel <nyguel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/07 18:36:38 by nyguel            #+#    #+#             */
/*   Updated: 2014/02/07 18:36:41 by nyguel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <math.h>
#include <stdlib.h>

float		*ft_vec_min(float a[3], float b[3])
{
	float	*tmp;
	int		i;

	tmp = (float *)malloc(sizeof(float) * 3);
	i = 0;
	while (i < 3)
	{
		tmp[i] = a[i] - b[i];
		i++;
	}
	return (tmp);
}



float		*ft_norm_vect(float *vect)
{
	float	sum;
	int		i;

	sum = sqrtf(vect[0] * vect[0] + vect[1] * vect[1] + vect[2] * vect[2]);
	i = 0;
	while (i < 3)
	{
		vect[i] = vect[i] / sum;
		i++;
	}
	return (vect);
}

float		*ft_intxvect(float x, float vect[3])
{
	int		i;
	float	*ret;

	ret = (float *)malloc(sizeof(float) * 3);
	i = 0;
	while (i < 3)
	{
		ret[i] = vect[i] * x;
		i++;
	}
	return (ret);
}

float		*ft_prod_vect(float u[3], float v[3])
{
	float	*pro;

	pro = (float *)malloc(sizeof(float) * 3);
	pro[0] = u[1] * v[2] - u[2] * v[1];
	pro[1] = u[2] * v[0] - u[0] * v[2];
	pro[2] = u[0] * v[1] - u[1] * v[0];
	return (pro);
}
