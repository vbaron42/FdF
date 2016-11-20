/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FdF.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbaron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/01 22:43:45 by vbaron            #+#    #+#             */
/*   Updated: 2016/11/19 18:58:29 by vbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include "libft/libft.h"
# include <mlx.h>
# define TILE_WIDTH 60
# define TILE_HEIGHT 40
# define P_HEIGHT 1
# define WIN_LEN 700
# define WIN_HEIGHT 750
# define SPEED 30
# define SCALE_POWER 1

typedef struct		s_point
{
	int				x;
	int				y;
	int				z;
	int				c;
	void			*next;
}					t_point;

typedef struct		s_line_data
{
	int				dx;
	int				dy;
	int				ix;
	int				iy;
	int				err;
	int				e;
}					t_line_data;

typedef struct		s_img
{
	void			*ptr;
	int				bpp;
	int				line_size;
	int				endian;
	char			*pxl_byt;
}					t_img;

typedef struct		s_env
{
	int				rl;
	int				bf;
	int				ud;
	int				scale;
	int				xmax;
	int				ymax;
	int				zmax;
	void			*mlx;
	void			*win;
	t_img			*img;
	t_point			*p;
	int				error;
}					t_env;

int					event(int keycode, t_env *env);
t_img				*new_img(t_env *env);
int					print_img(t_env *env);
t_point				*get_map(char *file);
t_point				ortho_to_iso(t_point p, t_env env);
void				draw_map(t_point *p, t_env *env);
#endif
