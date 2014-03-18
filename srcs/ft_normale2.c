/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_normale2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyguel <nyguel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/15 19:51:13 by nyguel            #+#    #+#             */
/*   Updated: 2014/03/15 19:51:15 by nyguel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <stdlib.h>

float	*ft_sel_norm(float *norm, t_ray *ray)
{
	float	*tmp;
	float	scal;

	ray->ins = 0;
	tmp = ft_intxvect(ray->d, ray->v);
	scal = ft_prod_scal(norm, tmp);
	free(tmp);
	if (scal > 0)
	{
		norm[0] = -1 * norm[0];
		norm[1] = -1 * norm[1];
		norm[2] = -1 * norm[2];
		if (ray->o_nb / MAX_OBJ != 2)
			ray->ins = 1;
	}
	return (norm);
}
