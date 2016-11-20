/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbaron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/07 16:50:50 by vbaron            #+#    #+#             */
/*   Updated: 2016/11/19 18:50:35 by vbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <fcntl.h>

t_point				*ft_lstadd_p(t_point *p, int x, char *str, int z)
{
	t_point			*newp;
	t_point			*tmp;

	newp = (t_point *)malloc(sizeof(t_point));
	newp->x = x;
	newp->y = ft_atoi(str);
	newp->z = z;
	newp->c = ft_atoi_16(str);
	if ((newp->c = ft_atoi_16(str)) == 0)
		newp->c = 0xFFFFFF;
	if (newp)
		newp->next = NULL;
	if (p == NULL)
		return (newp);
	tmp = p;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = newp;
	return (p);
}

t_point				*fill_p(int fd)
{
	t_point			*p;
	char			**str;
	char			*line;
	int				x;
	int				z;

	p = NULL;
	if (!(line = ft_strnew(1)))
		return (NULL);
	z = 0;
	while ((x = get_next_line(fd, &line)) != 0)
	{
		if (x == -1)
			return (NULL);
		x = 0;
		str = ft_strsplit_mo(line, ' ', '	', ' ');
		while (str[x] != NULL)
		{
			p = ft_lstadd_p(p, x, str[x], z);
			x++;
		}
		z++;
	}
	return (p);
}

t_point				*get_map(char *file)
{
	int				fd;
	t_point			*p;

	if ((!(ft_strstr(file, ".fdf")))
			|| (fd = open(file, O_RDONLY)) == -1
			|| (!(p = fill_p(fd))))
		return (NULL);
	close(fd);
	return (p);
}

void				get_max(t_env *env)
{
	t_point			*tmp;

	tmp = env->p;
	while (tmp != NULL)
	{
		if (env->xmax < tmp->x)
			env->xmax = tmp->x;
		if (env->ymax < tmp->y)
			env->ymax = tmp->y;
		if (env->zmax < tmp->z)
			env->zmax = tmp->z;
		tmp = tmp->next;
	}
	env->scale = WIN_LEN / (env->xmax + env->zmax / 2);
	tmp = env->p;
	while (tmp != NULL)
	{
		*tmp = ortho_to_iso(*tmp, *env);
		tmp = tmp->next;
	}
	draw_map(env->p, env);
}

int					main(int argc, char **argv)
{
	t_point			*p;
	t_env			*env;
	void			*mlx;
	void			*win;

	if (argc != 2 || (p = get_map(argv[1])) == NULL)
		return (-1);
	if (!(env = (t_env*)malloc(sizeof(t_env))))
		return (-1);
	env->rl = 0;
	env->bf = 0;
	env->ud = 0;
	if (!(env->mlx = mlx_init()))
		return (-1);
	if (!(env->win = mlx_new_window(env->mlx, WIN_LEN, WIN_HEIGHT, "title")))
		return (-1);
	if (!(env->img = new_img(env)))
		return (-1);
	env->p = p;
	get_max(env);
	ft_putstr("hook entrance :\n");
	mlx_key_hook(env->win, event, env);
	mlx_expose_hook(env->win, print_img, env);
	mlx_loop(env->mlx);
	return (0);
}
