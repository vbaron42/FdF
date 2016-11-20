/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ortho_to_iso.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbaron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/19 18:51:49 by vbaron            #+#    #+#             */
/*   Updated: 2016/11/20 13:37:24 by vbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_point				ortho_to_iso(t_point ort_p, t_env env)
{
	t_point			iso_p;

	iso_p = ort_p;
	iso_p.z = ort_p.y;
	iso_p.x = (ort_p.x - ort_p.z) * (env.scale / 2);
	iso_p.y = (ort_p.x + ort_p.z - (ort_p.y)) * (env.scale / 2);
	iso_p.x += WIN_LEN / 2;
	iso_p.y += WIN_HEIGHT / 10;
	return (iso_p);
}
