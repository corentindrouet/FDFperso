/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   affiche.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdrouet <cdrouet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/10 08:14:01 by cdrouet           #+#    #+#             */
/*   Updated: 2016/02/15 11:57:37 by cdrouet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

t_pts	init_pts(t_pts base, int i, int y)
{
	t_pts	ret;

	ret.x = base.x * i;
	ret.y = base.y * y;
	return (ret);
}

t_pts	decal(t_pts base, int x, int y)
{
	t_pts	ret;

	ret.x = base.x + x;
	ret.y = base.y + y;
	return (ret);
}

int		do_char_len(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	trace_droite(t_pt_af all, t_img *put, t_move param)
{
	while (param.carte->split[all.com.x])
	{
		if (param.carte->split[all.com.x + 1])
			trace_segment(decal(init_pts(all.init, all.com.x, all.com.y),
				all.dec.x, ((all.dec.y - (param.zoom *
					ft_atoi(param.carte->split[all.com.x]))) / 2)),
						decal(init_pts(all.init, all.com.x + 1, all.com.y),
							all.dec.x, ((all.dec.y + param.angle.y -
								(param.zoom * ft_atoi(
									param.carte->split[all.com.x + 1])))
										/ 2)), put);
		if (param.carte->next)
			if (all.com.x < do_char_len(param.carte->next->split))
				trace_segment(decal(init_pts(all.init, all.com.x, all.com.y),
					all.dec.x, ((all.dec.y - (param.zoom *
						ft_atoi(param.carte->split[all.com.x]))) / 2)),
							decal(init_pts(all.init, all.com.x, all.com.y + 1),
								all.dec.x - param.angle.x, ((all.dec.y -
									(param.zoom * ft_atoi(
										param.carte->next->split[all.com.x])))
											/ 2)), put);
		all.com.x++;
		all.dec.y += param.angle.y;
	}
}

void	affiche_carte(t_move param)
{
	t_img	*put;
	t_pt_af	all;

	all.tempo = param.angle.x;
	initialise_affiche(&param, &(all.init), &(all.dec), &put);
	all.com.y = 0;
	while (param.carte)
	{
		all.com.x = 0;
		all.dec.y = param.start.y + (param.angle.y * all.tempo);
		trace_droite(all, put, param);
		all.dec.x -= param.angle.x;
		all.com.y++;
		param.carte = param.carte->next;
	}
	mlx_put_image_to_window(param.omlx.mlx, param.omlx.win, put->img, 0, 0);
	mlx_destroy_image(param.omlx.mlx, put->img);
}
