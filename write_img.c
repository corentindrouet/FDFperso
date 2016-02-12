/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_img.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdrouet <cdrouet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/08 13:48:06 by cdrouet           #+#    #+#             */
/*   Updated: 2016/02/12 09:16:19 by cdrouet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

int		write_img(int x, int y, t_img *jpg)
{
	if (x < jpg->coord.x && x >= 0 && y < jpg->coord.y && y >= 0)
	{
		jpg->ret[(x * jpg->sl) + (y * jpg->bits / 8)] =
			(jpg->color & 0x00FF0000) >> 16;
		jpg->ret[(x * jpg->sl) + (y * jpg->bits / 8) + 1] =
			(jpg->color & 0x00FF00) >> 8;
		jpg->ret[(x * jpg->sl) + (y * jpg->bits / 8) + 2] =
			(jpg->color & 0x00FF) >> 0;
		return (1);
	}
	return (1);
}
