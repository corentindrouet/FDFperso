/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdrouet <cdrouet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/08 08:31:02 by cdrouet           #+#    #+#             */
/*   Updated: 2016/02/08 13:28:02 by cdrouet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

t_img	*t_img_init(void *mlx, int x, int y)
{
	t_img	*res;

	res = (t_img*)malloc(sizeof(t_img));
	res->img = mlx_new_image(mlx, x, y);
	res->ret = mlx_get_data_addr(res->img, &(res->bits), &(res->sl), &(res->endian));
	return (res);
}
