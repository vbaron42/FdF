/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbaron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/07 16:50:50 by vbaron            #+#    #+#             */
/*   Updated: 2016/11/15 08:19:01 by vbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <fcntl.h>
/*
int				press_t(int keycode, t_point p)
{
	ft_putstr("Appuie sur l !\n");
	if (keycode == 37)
	{
		p.x++;
		mlx_pixel_put(p.mlx, p.win, p.x, p.y, 0x00FFFFFF);
	}
	return (0);
}*/

//int				*get_size_map()
/*
int				get_dim(int fd, int *xlen, int *zwid)
{
	int			gnl_ret;
	char		**str;
	char		**line;

	if (!(*line = ft_strnew(1)))
		return (-1);
	while ((gnl_ret = get_next_line(fd, line)) > 0)
	{
		str = ft_strsplit(*line, ' ');//ft_free line et str ?
		while (str[*xlen] != NULL)
			*xlen++;
		*zwid++;
	}
	return (gnl_ret);
}
*/
t_point			*ft_lstadd_p(t_point *p, int x, char *str, int z)
{
	t_point		*newp;
	t_point		*tmp;

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

t_point			*fill_p(int fd)
{
	t_point		*p;
	char		**str;
	char		*line;
	int			x;
	int			z;

	p = NULL;
	if (!(line = ft_strnew(1)))
		return (NULL);
	z = 0;
	while ((x = get_next_line(fd, &line)) != 0)
	{
		if (x == -1)
			return (NULL);
		x = 0;
		str = ft_strsplit(line, ' ');//ft_free str et line ?
		while (str[x] != NULL)
		{
			p = ft_lstadd_p(p, x, str[x], z);
			x++;
		}
		z++;
	}
	return (p);
}

t_point			*get_map(char *file)
{
	int			fd;
	t_point		*p;

	if ((!(ft_strstr(file, ".fdf")))
			|| (fd = open(file, O_RDONLY)) == -1
			|| (!(p = fill_p(fd))))
		return (NULL);
	close(fd);
	return (p);
}

t_point				ortho_to_iso(t_point ort_p, t_env env)
{
	t_point			iso_p;

	iso_p = ort_p;
	iso_p.x = (ort_p.x - ort_p.z) * (env.scale / 2);
	iso_p.y = (ort_p.x + ort_p.z - (ort_p.y)) * (env.scale / 2);
	iso_p.x += WIN_LEN / 2;
	iso_p.y += WIN_HEIGHT / 10;
	return (iso_p);
}

int				key_hook(int code, t_env *env)
{
	ft_putnbr(code);
	ft_putchar('\n');
	if (code == 53)
	{
		mlx_destroy_window(env->mlx, env->win);
		exit(0);
	}
	if (code == 0)
		env->rl -= 1 * SPEED;
	if (code == 2)
		env->rl += 1 * SPEED;
	if (code == 1)
		env->bf += 1 * SPEED;
	if (code == 13)
		env->bf -= 1 * SPEED;
	if (code == 49)
		env->ud += 1 * SPEED;
	if (code == 257)
		env->ud -= 1 * SPEED;
	if (code == 69)
		env->scale += 1 * SCALE_POWER;
	if (code == 78)
		env->scale -= 1 * SCALE_POWER;
//	matricialisation(env); Dans le prochaine episode !
	return (0);
}//colorier soi meme la map :) avec le curseur et les touches

int				redim(t_env *env)
{
//changement de dimension de la fenettre ?
	return (0);
}

int				main(int argc, char **argv)
{
	t_point		*p;
	t_point		*tmp;
	t_env		*env;
	int			prevx;
	int			prevz;
	void		*mlx;
	void		*win;

	if (argc != 2 || (p = get_map(argv[1])) == NULL)
		return (-1);
	if (!(env = (t_env*)malloc(sizeof(t_env))))
		return (-1);
//	env->p = p;
//	&p = env;//ajout de p dans env
	env->rl = 0;
	env->bf = 0;
	env->ud = 0;
	if (!(env->mlx = mlx_init()))
		return (-1);
	if (!(env->win = mlx_new_window(env->mlx, WIN_LEN, WIN_HEIGHT, "title")))
		return (-1);
	tmp = p;
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
//valeurs modifiable et sans precision necessaire (ajustement final)
	tmp = p;
	while (tmp != NULL)
	{
		*tmp = ortho_to_iso(*tmp, *env);
		tmp = tmp->next;
	}
	if (draw_map(p, env) == -1)
		return (-1);//fermer la fenetre et exit
//	tmp = p;
//	while (tmp != NULL)
//	{
//		mlx_pixel_put(env->mlx, env->win, tmp->x, tmp->y, 0x00FFFF);
//		tmp = tmp->next;
//	}

//		if (tmp->z != 0)
//			segment_put(prevx, prevz, tmp->x, tmp->z, mlx, win);
//		prevx = tmp->x;
//		prevz = tmp->z;
//	ft_lstmap(p, (*modif_p));
//	verifier avant de poser un pixel si il est dans l'ecran et gerer les deplacement en decalant tout les points (utiliser fleches) pour le zoom utiliser TILE_...
//
	mlx_expose_hook(env->win, redim, env);
	mlx_key_hook(env->win, key_hook, env);
	mlx_loop(env->mlx);
	return (0);
}
