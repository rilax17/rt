/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atod.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evilsbol <evilsbol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/21 15:14:05 by evilsbol          #+#    #+#             */
/*   Updated: 2014/03/21 15:14:06 by evilsbol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double			ft_atod(char *str)
{
	double		res;
	double		fact;
	double		dot_seen;

	res = 0;
	fact = 1;
	dot_seen = 0;
	while (*str == ' ')
		str++;
	if (*str == '+' || *str == '-')
		fact = (*str == '-' ? (str++, -1) : (str++, 1));
	while ((ft_isdigit(*str) || *str == '.') && *str != '\0')
	{
		if (dot_seen == 0 && *str == '.')
			dot_seen = 1;
		else if (ft_isdigit(*str))
		{
			if (dot_seen)
				fact /= 10.0;
			res = res * 10.0 + (double)(*str - '0');
		}
		str++;
	}
	return (res * fact);
}