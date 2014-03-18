/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arraysrt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evilsbol <evilsbol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/26 16:31:11 by evilsbol          #+#    #+#             */
/*   Updated: 2014/02/26 16:31:13 by evilsbol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_arraysrt(char **array)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!array)
		return (-1);
	while (array[i][0])
	{
		j = i + 1;
		while (array[j][0] != '\0')
		{
			if (ft_strcmp(array[i], array[j]) > 0)
				ft_swap(&(array[i]), &(array[j]));
			j++;
		}
		i++;
	}
	return (0);
}
