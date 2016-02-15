/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   affiche.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdrouet <cdrouet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/10 08:14:01 by cdrouet           #+#    #+#             */
/*   Updated: 2016/02/15 09:18:22 by cdrouet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

static t_pts	init_pts(t_pts base, int i, int y)
{
	t_pts	ret;

	ret.x = base.x * i;
	ret.y = base.y * y;
	return (ret);
}

static t_pts	decal(t_pts base, int x, int y)
{
	t_pts	ret;

	ret.x = base.x + x;
	ret.y = base.y + y;
	return (ret);
}

int				do_char_len(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int				lst_len(t_file *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}

void			affiche_carte(t_move param)
{
	t_pts	com;
	t_pts	init;
	t_pts	dec;
	t_img	*put;
	int		tempo;

	tempo = param.angle.x;
	initialise_affiche(&param, &init, &dec, &put);
	com.y = 0;
	while (param.carte)
	{
		com.x = 0;
		dec.y = param.start.y + (param.angle.y * tempo);
		while (param.carte->split[com.x])
		{
			if (param.carte->split[com.x + 1])
				trace_segment(decal(init_pts(init, com.x, com.y), dec.x,
					((dec.y - (param.zoom *
						ft_atoi(param.carte->split[com.x]))) / 2)),
							decal(init_pts(init, com.x + 1, com.y), dec.x,
								((dec.y + param.angle.y - (param.zoom *
									ft_atoi(param.carte->split[com.x + 1])))
										/ 2)), put);
			if (param.carte->next)
				if (com.x < do_char_len(param.carte->next->split))
					trace_segment(decal(init_pts(init, com.x, com.y), dec.x,
						((dec.y - (param.zoom *
							ft_atoi(param.carte->split[com.x]))) / 2)),
								decal(init_pts(init, com.x, com.y + 1),
									dec.x - param.angle.x, ((dec.y -
										(param.zoom * ft_atoi(
											param.carte->next->split[com.x])))
												/ 2)), put);
			com.x++;
			dec.y += param.angle.y;
		}
		dec.x -= param.angle.x;
		com.y++;
		param.carte = param.carte->next;
	}
	mlx_put_image_to_window(param.omlx.mlx, param.omlx.win, put->img, 0, 0);
	mlx_destroy_image(param.omlx.mlx, put->img);
}
