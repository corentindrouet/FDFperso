/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   segment.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdrouet <cdrouet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/08 13:10:04 by cdrouet           #+#    #+#             */
/*   Updated: 2016/02/12 09:27:42 by cdrouet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

static void	first_ca(t_pts d, t_pts start, t_pts stop, t_img *jpg)
{
	int		e;

	if (d.x >= d.y)
	{
		e = d.x;
		d.x *= 2;
		d.y *= 2;
		while (start.x != stop.x && write_img(start.y, start.x++, jpg))
			if ((e -= d.y) < 0)
			{
				start.y++;
				e += d.x;
			}
	}
	else
	{
		e = d.y;
		d.x *= 2;
		d.y *= 2;
		while (start.y != stop.y && write_img(start.y++, start.x, jpg))
			if ((e -= d.x) < 0)
			{
				start.x++;
				e += d.y;
			}
	}
}

static void	last_ca(t_pts d, t_pts start, t_pts stop, t_img *jpg)
{
	int		e;

	if (d.x >= -d.y)
	{
		e = d.x;
		d.x *= 2;
		d.y *= 2;
		while (start.x != stop.x && write_img(start.y, start.x++, jpg))
			if ((e += d.y) < 0)
			{
				start.y--;
				e += d.x;
			}
	}
	else
	{
		e = d.y;
		d.x *= 2;
		d.y *= 2;
		while (start.y != stop.y && write_img(start.y--, start.x, jpg))
			if ((e += d.x) > 0)
			{
				start.x++;
				e += d.y;
			}
	}
}

static void	second_ca(t_pts d, t_pts start, t_pts stop, t_img *jpg)
{
	int		e;

	if (-d.x >= d.y)
	{
		e = d.x;
		d.x *= 2;
		d.y *= 2;
		while (start.x != stop.x && write_img(start.y, start.x--, jpg))
			if ((e += d.y) >= 0)
			{
				start.y++;
				e += d.x;
			}
	}
	else
	{
		e = d.y;
		d.x *= 2;
		d.y *= 2;
		while (start.y != stop.y && write_img(start.y++, start.x, jpg))
			if ((e += d.x) <= 0)
			{
				start.x--;
				e += d.y;
			}
	}
}

static void	third_ca(t_pts d, t_pts start, t_pts stop, t_img *jpg)
{
	int		e;

	if (d.x <= d.y)
	{
		e = d.x;
		d.x *= 2;
		d.y *= 2;
		while (start.x != stop.x && write_img(start.y, start.x--, jpg))
			if ((e -= d.y) >= 0)
			{
				start.y--;
				e += d.x;
			}
	}
	else
	{
		e = d.y;
		d.x *= 2;
		d.y *= 2;
		while (start.y != stop.y && write_img(start.y--, start.x, jpg))
			if ((e -= d.x) >= 0)
			{
				start.x--;
				e += d.y;
			}
	}
}

void		trace_segment(t_pts start, t_pts stop, t_img *jpg)
{
	t_pts	d;

	d.x = stop.x - start.x;
	d.y = stop.y - start.y;
	if (d.x > 0)
	{
		if (d.y > 0)
			first_ca(d, start, stop, jpg);
		else if (d.y < 0)
			last_ca(d, start, stop, jpg);
		else
			while (start.x != stop.x)
				write_img(start.y, start.x++, jpg);
	}
	else if (d.x < 0)
	{
		if (d.y > 0)
			second_ca(d, start, stop, jpg);
		else if (d.y < 0)
			third_ca(d, start, stop, jpg);
		else
			while (start.x != stop.x)
				write_img(start.y, start.x--, jpg);
	}
	else
	{
		if (d.y > 0)
			while (start.y != stop.y)
				write_img(start.y++, start.x, jpg);
		else if (d.y < 0)
			while (start.y != stop.y)
				write_img(start.y--, start.x, jpg);
	}
}
