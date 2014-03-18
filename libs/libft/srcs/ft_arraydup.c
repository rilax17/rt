/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arraydup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evilsbol <evilsbol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/25 14:51:39 by evilsbol          #+#    #+#             */
/*   Updated: 2014/02/25 14:56:05 by evilsbol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_arraydup(char **array)
{
	int		i;
	int		len;
	char	**cpy;

	i = -1;
	len = ft_arraylen((void **)array);
	cpy = (char **)malloc(sizeof(char *) * len + 1);
	while (array && array[++i])
		cpy[i] = ft_strdup(array[i]);
	cpy[i] = NULL;
	return (cpy);
}
