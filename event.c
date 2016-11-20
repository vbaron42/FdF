/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbaron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/17 02:32:14 by vbaron            #+#    #+#             */
/*   Updated: 2016/11/19 18:57:21 by vbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void			color_map(t_env *env)
{
	t_point		*tmp;

	tmp = env->p;
	while (tmp != NULL)
	{
		if (tmp->z <= 0)
			tmp->c = 0x00CCFF;
		if (tmp->z > 0 && tmp->z <= 2)
			tmp->c = 0xFFCC33;
		if (tmp->z > 2 && tmp->z <= 4)
			tmp->c = 0xFF9933;
		if (tmp->z > 4 && tmp->z <= 10)
			tmp->c = 0x336600;
		if (tmp->z > 10 && tmp->z <= 14)
			tmp->c = 0x999999;
		if (tmp->z > 14)
			tmp->c = 0xCCFFFF;
		tmp = tmp->next;
	}
}

void			key_hook(int code, t_env *env)
{
	env->rl = 0;
	env->ud = 0;
	env->scale = 1;
	if (code == 123)
		env->rl -= 1 * SPEED;
	if (code == 124)
		env->rl += 1 * SPEED;
	if (code == 125)
		env->ud += 1 * SPEED;
	if (code == 126)
		env->ud -= 1 * SPEED;
	if (code == 69)
		env->scale = 1 + SCALE_POWER;
	if (code == 78)
		env->scale = 1.5 - SCALE_POWER;
	if (code == 8)
		color_map(env);
}

int				event(int code, t_env *env)
{
	t_point		*tmp;

	if (code == 53)
	{
		mlx_destroy_window(env->mlx, env->win);
		exit(0);
	}
	key_hook(code, env);
	tmp = env->p;
	while (tmp != NULL)
	{
		tmp->y += env->ud;
		tmp->x += env->rl;
		tmp->x = env->scale * tmp->x;
		tmp->y = env->scale * tmp->y;
		tmp = tmp->next;
	}
	print_img(env);
	return (0);
}
