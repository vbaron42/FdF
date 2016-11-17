/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbaron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/17 02:32:14 by vbaron            #+#    #+#             */
/*   Updated: 2016/11/17 04:18:53 by vbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int				key_hook(int code, t_env *env)
{
	t_point		*tmp;

	tmp = env->p;
	ft_putchar('\n');
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
	ft_putnbr(env->rl);
	while (tmp != NULL)
	{
		tmp->x += env->rl;
		tmp = tmp->next;
	}
	ft_putchar(' ');
	ft_putnbr(env->p->x);
//	matricialisation(env); Dans le prochaine episode !
	return (0);
}//colorier soi meme la map :) avec le curseur et les touches

int		event(int code, t_env *env)
{
	if (code == 53)
	{
		mlx_destroy_window(env->mlx, env->win);
		exit(0);
	}
	key_hook(code, env);
	print_img(env);
	return (0);
}
