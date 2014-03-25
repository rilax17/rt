/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_tools.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evilsbol <evilsbol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/21 15:05:49 by evilsbol          #+#    #+#             */
/*   Updated: 2014/03/21 15:05:51 by evilsbol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	rt_get_int(char *line, int *tab, size_t size)
{
	int		i;
	int		j;
	char	**tmp;

	if (line && tab)
	{
		i = 0;
		j = 1;
		tmp = ft_strsplit(line, ' ');
		while (tmp && tmp[j] && (tab[i] < size))
			tab[i++] = ft_atoi(tmp[j++]);
	}
}

void	rt_get_float(char *line, float *tab, size_t size)
{
	int		i;
	int		j;
	char	**tmp;

	if (line && tab)
	{
		i = 0;
		j = 1;
		tmp = ft_strsplit(line, ' ');
		while (tmp && tmp[j] && (tab[i] < size))
			tab[i++] = ft_atof(tmp[j++]);
	}
}

void	rt_init_int(int *tab, int size)
{
	int		i;

	i = 0;
	while (i < size)
		tab[i++] = 0;
}

void	rt_init_float(float *tab, int size)
{
	int		i;

	i = 0;
	while (i < size)
		tab[i++] = 0;
}