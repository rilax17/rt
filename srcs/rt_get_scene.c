/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_get_scene.c                                     :+:      :+:    :+:   */
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

void	rt_get_data(int fd, char *line, t_env *env)
{
	while (get_next_line(fd, &line) > 0)
	{
		if (ft_strstr(line, "camera"))
			rt_get_cam(fd, env->dt);
		else if (ft_strstr(line, "sphere"))
			rt_get_sph(fd, env->obj);
		else if (ft_strstr(line, "cylinder"))
			rt_get_cyl(fd, env->obj);
		else if (ft_strstr(line, "planes"))
			rt_get_pln(fd, env->obj);
		else if (ft_strstr(line, "spots"))
			rt_get_spt(fd, env->obj);
		else
			ft_printf("%s\n", line);
	}

}


void	rt_get_scene(char *file, t_env *env)
{
	int		fd;
	char	*line;

	if ((fd = open(file, O_RDONLY)) > 0)
	{
		while (get_next_line(fd, &line) > 0)
		{
			if (ft_strstr(line, "scene"))
				rt_get_data(fd, line, env);
			else
				ft_printf("%s\n", line);
		}
	}
	else
		ft_quit(ENOENT, "could not open requested file");
}

// void	rt_set_cam(t_dt *dt)
// {
// 	dt->zoom = ZOOM;
// 	dt->cam_pos[0] = 0;
// 	dt->cam_pos[1] = -ZOOM;
// 	dt->cam_pos[2] = 0;
// 	dt->opt_f = 0;
// 	dt->delta = 10;
// }
