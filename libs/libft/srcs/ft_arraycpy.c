/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arraycpy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evilsbol <evilsbol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/25 14:47:41 by evilsbol          #+#    #+#             */
/*   Updated: 2014/02/25 14:50:33 by evilsbol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_arraycpy(char **dest, char **src)
{
	int		i;

	i = 0;
	while (src[i])
	{
		if (!(dest[i] = ft_strdup(src[i])))
			return (0);
		i++;
	}
	dest[i] = NULL;
	return (1);
}
