/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_get_data.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evilsbol <evilsbol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/18 17:08:18 by evilsbol          #+#    #+#             */
/*   Updated: 2014/03/18 17:08:19 by evilsbol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
** if no file specified, prompt user.
** if file, open, read file.
*/
void	rt_get_data(char *file, t_env *env)
{
	int		fd;
	char	*line;

	if ((fd = open(file, O_RDONLY)) > 0)
	{
		//if line == camera then rt_set_cam
		rt_set_cam(env->dt);
		
	}
	else
		ft_quit(ENOENT, "could not open requested file");
}

void	rt_set_cam(t_dt *dt)
{
	dt->zoom = ZOOM;
	dt->cam_pos[0] = 0;
	dt->cam_pos[1] = -ZOOM;
	dt->cam_pos[2] = 0;
	dt->opt_f = 0;
	dt->delta = 10;
}
