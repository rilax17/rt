/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyguel <nyguel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/16 19:07:21 by nyguel            #+#    #+#             */
/*   Updated: 2014/02/16 19:07:23 by nyguel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int			ft_get_next_inter(t_ray *ray, t_obj *obj)
{
	int		i;
	int		max;

	max = MAX_OBJ;
	i = 0;
	while (i < obj->nb_o[1])
	{
		if (max + i != ray->o_nb && ray->o_d[max + i] - ray->d < ray->delta)
			return (1);
		i++;
	}
	i = 0;
	while (i < obj->nb_o[2])
	{
		if (2 * max + i != ray->o_nb && ray->o_d[2 * max + i]
				- ray->d < ray->delta)
			return (1);
		i++;
	}
	return (0);
}

int			ft_strlen(char *s)
{
	int		i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}
