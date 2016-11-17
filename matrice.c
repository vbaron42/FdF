/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrice.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbaron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/13 03:12:00 by vbaron            #+#    #+#             */
/*   Updated: 2016/11/16 23:55:50 by vbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

t_point			*matrice(t_point *p, t_move m)
{
	y_point		pnew;
	int			f[4][4];
	int			i;
	int			i2;

	i = 0;
	while (i < 4)
	{
		i2 = 0;
		while (i2 < 4)
		{
			f[i][i2] = 0;//temporaire ?
			if (i == i2)
				f[i][i2] = m->scale;
			i2++;
		}
		f[i][3] = m->pos[i]
		i++;
	}
	pnew->x = f[0][0] * p->x + f[0][1] * p->y + f[0][2] * p->z + f[0][3] * p->w;
	pnew->y = f[1][0] * p->x + f[1][1] * p->y + f[1][2] * p->z + f[1][3] * p->w;
	pnew->z = f[2][0] * p->x + f[2][1] * p->y + f[2][2] * p->z + f[2][3] * p->w;
	pnew->w = f[3][0] * p->x + f[3][1] * p->y + f[3][2] * p->z + f[3][3] * p->w;

	pnew->next;
	return (pnew);
}
/*
	while (i < 4)
	{
		f[i][i] = m->scale;
	}
	f[0][3] = m->xpos;
	f[1][3] = m->ypos;
	*/
