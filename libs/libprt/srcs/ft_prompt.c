/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evilsbol <evilsbol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/25 15:28:35 by evilsbol          #+#    #+#             */
/*   Updated: 2014/02/25 15:29:35 by evilsbol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libprt.h"

void	ft_prompt(char *prompt, char *color)
{
	ft_printf("%s%s%s", color, prompt, RESET);
	return ;
}
