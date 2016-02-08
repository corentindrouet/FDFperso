/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   segment.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdrouet <cdrouet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/08 13:10:04 by cdrouet           #+#    #+#             */
/*   Updated: 2016/02/08 13:35:04 by cdrouet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	first_ca(t_pts d, t_pts start, t_pts stop, t_img *jpg)
{
	int		e;

	if (d.x >= d.y)
	{
		e = d.x;
		d.x *= 2;
		d.y *= 2;
		while (start.x != stop.x)
		{
			jpg->ret[start.x * jpg->sl + start.y * jpg->bits / 8] = (jpg->color & 0x00FF0000) >> 16;
			jpg->ret[start.x * jpg->sl + start.y * jpg->bits / 8 + 1] = (jpg->color & 0x00FF00) >> 8;
			jpg->ret[start.x * jpg->sl + start.y * jpg->bits / 8 + 2] = (jpg->color & 0x00FF) >> 0;
			if ((e -= d.y) < 0)
			{
				start.y++;
				e += d.x;
			}
		}
	}
	else
	{
		e = d.y;
		d.x *= 2;
		d.y *= 2;
		while (start.y != stop.y)
		{
			jpg->ret[start.x * jpg->sl + start.y * jpg->bits / 8] = (jpg->color & 0x00FF0000) >> 16;
			jpg->ret[start.x * jpg->sl + start.y * jpg->bits / 8 + 1] = (jpg->color & 0x00FF00) >> 8;
			jpg->ret[start.x * jpg->sl + start.y * jpg->bits / 8 + 2] = (jpg->color & 0x00FF) >> 0;
			if ((e -= d.x) < 0)
			{
				start.x++;
				e += d.y;
			}
		}
	}
}

void		trace_segment(t_pts start, t_pts stop, t_img *jpg)
{
	t_pts	d;

	d.x = stop.x - start.x;
	d.y = stop.y - start.y;
	if (d.x != 0)
	{
		if (d.x > 0)
		{
			if (d.y != 0)
			{
				if (d.y > 0)
				{
				}
			}
		}
	}
}
