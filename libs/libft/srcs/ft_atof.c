/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evilsbol <evilsbol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/21 15:48:15 by evilsbol          #+#    #+#             */
/*   Updated: 2014/03/21 15:48:16 by evilsbol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

float	ft_atof(char *str)
{
	float	rez;
	float	fact;
	int		dot_seen;

	rez = 0;
	fact = 1;
	dot_seen = 0;
	while (*str == ' ')
		str++;
	if (*str == '-' || *str == '+')
		fact = *str == '-' ? (str++, -1) : (str++, 1);
	while ((ft_isdigit(*str) || *str == '.') && *str != '\0')
	{
		if (dot_seen == 0 && *str == '.')
			dot_seen = 1;
		else if (ft_isdigit(*str))
		{
			if (dot_seen)
				fact /= 10.0f;
			rez = rez * 10.0f + (float)(*str - '0');
		}
		str++;
	}
	return (rez * fact);
};