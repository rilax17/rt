/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_inside_cocy.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyguel <nyguel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/15 19:54:27 by nyguel            #+#    #+#             */
/*   Updated: 2014/03/15 19:54:29 by nyguel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

float	ft_inside_co(t_ray *ray, float d[5], float ret, int i)
{
	ray->o_dneg[4 * MAX_OBJ + i] = -D_MAX;
	if (ret >= 0)
	{
		i = -1;
		while (++i < 4)
		{
			if (d[i] < 0)
			{
				if (d[i] > ray->o_dneg[4 * MAX_OBJ + i])
					ray->o_dneg[4 * MAX_OBJ + i] = d[i];
				if (d[i] > ray->dneg || ray->dneg == 0)
				{
					ray->dneg = d[i];
					ray->oneg_nb = 4 * MAX_OBJ + i;
				}
			}
		}
	}
	return (ret);
}

float	ft_inside_cy(t_ray *ray, float d[5], float ret, int i)
{
	ray->o_dneg[3 * MAX_OBJ + i] = -D_MAX;
	if (ret >= 0)
	{
		i = -1;
		while (++i < 4)
		{
			if (d[i] < 0)
			{
				if (d[i] > ray->o_dneg[3 * MAX_OBJ + i])
					ray->o_dneg[3 * MAX_OBJ + i] = d[i];
				if (d[i] > ray->dneg || ray->dneg == 0)
				{
					ray->dneg = d[i];
					ray->oneg_nb = 3 * MAX_OBJ + i;
				}
			}
		}
	}
	return (ret);
}
