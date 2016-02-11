/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   affiche.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdrouet <cdrouet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/10 08:14:01 by cdrouet           #+#    #+#             */
/*   Updated: 2016/02/11 14:12:35 by cdrouet          ###   ########.fr       */
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

void			affiche_carte(t_file *carte, t_mlx info, t_pts valdec, t_pts start)
{
	int		i;
	int		y;
	t_pts	init;
	t_pts	dec;
	t_img	*put;

	valdec.y = valdec.x * 0.4;
	init.x = ((do_char_len(carte->split) / 900) >= 1) ? do_char_len(carte->split) / 900 : valdec.x * 0.6;
	init.y = ((lst_len(carte) / 900) >= 1) ? lst_len(carte) / 900 : valdec.x * 0.8;
	put = t_img_init(info.mlx, 1000, 1000);
	dec.x = start.x;
	dec.y = start.y;
	y = 0;
	put->color = mlx_get_color_value(info.mlx, 0x0000FF);
	while (carte)
	{
		i = 0;
		dec.y = start.y;
		while (carte->split[i])
		{
			if (carte->split[i + 1])
				trace_segment(decal(init_pts(init, i, y), dec.x,
					((dec.y - ((valdec.x * 0.08) * ft_atoi(carte->split[i]))) / 2)),
						decal(init_pts(init, i + 1, y), dec.x,
							((dec.y + valdec.y - ((valdec.x * 0.08) * ft_atoi(carte->split[i + 1]))) / 2)), put);
			if (carte->next)
				if (i < do_char_len(carte->next->split))
					trace_segment(decal(init_pts(init, i, y), dec.x,
						((dec.y - ((valdec.x * 0.08) * ft_atoi(carte->split[i]))) / 2)),
							decal(init_pts(init, i, y + 1), dec.x - valdec.x,
								((dec.y - ((valdec.x * 0.08) * ft_atoi(carte->next->split[i]))) / 2)), put);
			i++;
			dec.y += valdec.y;
		}
		dec.x -= valdec.x;
		y++;
		carte = carte->next;
	}
	mlx_put_image_to_window(info.mlx, info.win, put->img, 0, 0);
	mlx_destroy_image(info.mlx, put->img);
}
