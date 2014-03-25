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

static void		rt_get_data(int fd, char *line, t_env *env)
{
	while (get_next_line(fd, &line) > 0)
	{
		if (ft_strstr(line, "camera{") || ft_strstr(line, "camera {") )
			rt_get_cam(fd, env->dt);
		else if (ft_strstr(line, "sphere"))
			rt_get_sph(fd, env->obj);
		else if (ft_strstr(line, "cylinder"))
			rt_get_cyl(fd, env->obj);
		else if (ft_strstr(line, "plane"))
			rt_get_pln(fd, env->obj);
		else if (ft_strstr(line, "spot"))
			rt_get_spt(fd, env->obj);
		else
			continue;
	}

}

void			rt_get_scene(char *file, t_env *env)
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
				continue;
		}
	}
	else
		ft_quit(ENOENT, "could not open requested file");
}
