/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdrouet <cdrouet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/05 09:53:37 by cdrouet           #+#    #+#             */
/*   Updated: 2016/02/05 14:01:03 by cdrouet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

int	esc_touch(int keycode, void *param)
{
	if (keycode == esc)
		exit(0);
	return (0);
}

int	main(void)
{
	t_mlx	prout;
	t_img	essai;
	int		b;
	int		i;
	unsigned long	o;

	prout.mlx = mlx_init();
	prout.win = mlx_new_window(prout.mlx, 400, 400, "prout");
	essai.img = mlx_new_image(prout.mlx, 100, 100);
	essai.ret = mlx_get_data_addr(essai.img, &(essai.bits), &(essai. size_line),
		&(essai.endian));
	/*i = -1;
	while (++i < 100)
	{
		b = -1;
		while (++b < 100)
			mlx_pixel_put(prout.mlx, essai.img, b, i, 0x00FFFFFF);
	}*/
	i = essai.bits;
	b = 0;
	o = mlx_get_color_value(prout.mlx, 0xFFFFFF);
	while (b < 400)
	{
		essai.ret[b] = (o & 0xFF000000) >> 24;
		essai.ret[b + 1] = (o & 0xFF0000) >> 16;
		essai.ret[b + 2] = (o & 0xFF00) >> 8;
		essai.ret[b + 3] = (o & 0xFF);
		b += 4;
	}
	mlx_put_image_to_window(prout.mlx, prout.win, essai.img, 100, 100);
	mlx_key_hook(prout.win, esc_touch, 0);
	mlx_loop(prout.mlx);
	return (0);
}
