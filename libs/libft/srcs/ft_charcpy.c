/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_charcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evilsbol <evilsbol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/27 16:08:29 by evilsbol          #+#    #+#             */
/*   Updated: 2014/02/27 16:08:31 by evilsbol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Copies the value of src[index] into dst[index] and closes string 
** at dst[index + 1]
*/

void	ft_charcpy(char *dst, char *src, int index)
{
	if (dst && src)
	{
		dst[index] = src[index];
		dst[index + 1] = '\0';
	}
}
