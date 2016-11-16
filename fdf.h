/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FdF.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbaron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/01 22:43:45 by vbaron            #+#    #+#             */
/*   Updated: 2016/11/15 06:14:00 by vbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include "libft/libft.h"
# include <mlx.h>
# define TILE_WIDTH 60
# define TILE_HEIGHT 40
# define P_HEIGHT 1
# define WIN_LEN 600
# define WIN_HEIGHT 650
# define SPEED 30
# define SCALE_POWER 30

typedef struct		s_point
{
	int				x;
	int				y;
	int				z;
	int				c;
	void			*next;
}					t_point;

typedef struct	s_line_data
{
	int			dx;
	int			dy;
	int			ix;
	int			iy;
	int			err;
	int			e;
}				t_line_data;

typedef struct		s_env
{
	int				rl;
	int				bf;
	int				ud;
	int				scale;
	int				xmax;//		a enlever du .h et a integrer
	int				ymax;//		dans une fonction
	int				zmax;//		pour trouver scale
	void			*mlx;
	void			*win;
//	t_point			*p;
	int				error;
}					t_env;

t_point				*get_map(char *file);
t_point				ortho_to_iso(t_point p, t_env env);
int					draw_map(t_point *p, t_env *env);
#endif
