/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdrouet <cdrouet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/05 09:53:37 by cdrouet           #+#    #+#             */
/*   Updated: 2016/02/08 13:28:26 by cdrouet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

int	esc_touch(int keycode, void *param)
{
	t_mlx	*prout;

	if (keycode == esc)
	{
		prout = (t_mlx*)param;
		mlx_destroy_window(prout->mlx, prout->win);
		exit(0);
	}
	return (0);
}

int	main(void)
{
	t_mlx	prout;
	t_img	*essai;
	t_pts	pt1;
	t_pts	pt2;
	int		b;
	int		i;
	unsigned long	o;

	prout.mlx = mlx_init();
	prout.win = mlx_new_window(prout.mlx, 600, 600, "prout");
	essai = t_img_init(prout.mlx, 100, 100);
	i = 0;
	b = 0;
	o = mlx_get_color_value(prout.mlx, 0xFFFFFF);
	while (b < 100)
	{
		essai->ret[(b * essai->sl) + (i * essai->bits / 8)] = (o & 0x00FF0000) >> 16;
		essai->ret[(b * essai->sl) + (i * essai->bits / 8) + 1] = (o & 0x00FF00) >> 8;
		essai->ret[(b * essai->sl) + (i * essai->bits / 8) + 2] = (o & 0x00FF) >> 0;
		b++;
		if (b == 100 && i < 100)
		{
			b = 0;
			i++;
		}
	}
	pt1.x = 0;
	pt1.y = 0;
	pt2.x = 80;
	pt2.y = 20;

	essai->color = mlx_get_color_value(prout.mlx, 0x0000FF);
	segment(essai, essai->color, pt1, pt2);
	mlx_put_image_to_window(prout.mlx, prout.win, essai->img, 100, 100);
	mlx_destroy_image(prout.mlx, essai->img);
	mlx_key_hook(prout.win, esc_touch, &prout);
	mlx_loop(prout.mlx);
	return (0);
}
