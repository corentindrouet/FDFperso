/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   affiche.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdrouet <cdrouet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/10 08:14:01 by cdrouet           #+#    #+#             */
/*   Updated: 2016/02/10 12:56:07 by cdrouet          ###   ########.fr       */
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

void			affiche_carte(t_file *carte, void *mlx, void *win, t_pts valdec)
{
	int		i;
	int		y;
	t_pts	init;
	t_pts	dec;
	t_img	*put;

	init.x = ((do_char_len(carte->split) / 900) >= 1) ? do_char_len(carte->split) / 900 : 15;
	init.y = ((lst_len(carte) / 900) >= 1) ? lst_len(carte) / 900 : 20;
	put = t_img_init(mlx, 900, 900);
	dec.x = lst_len(carte) * valdec.x;
	dec.y = do_char_len(carte->split) * valdec.y;
	y = 0;
	put->color = mlx_get_color_value(mlx, 0x0000FF);
	while (carte)
	{
		i = 0;
		dec.y = 0;
		while (carte->split[i])
		{
			if (carte->split[i + 1])
				trace_segment(decal(init_pts(init, i, y), dec.x, dec.y - ft_atoi(carte->split[i])),
					decal(init_pts(init, i + 1, y), dec.x, dec.y + valdec.y - ft_atoi(carte->split[i + 1])), put);
			if (carte->next)
				if (i < do_char_len(carte->next->split))
					trace_segment(decal(init_pts(init, i, y), dec.x, dec.y - ft_atoi(carte->split[i])),
						decal(init_pts(init, i, y + 1), dec.x - valdec.x, dec.y - ft_atoi(carte->next->split[i])), put);
			i++;
			dec.y += valdec.y;
		}
		dec.x -= valdec.x;
		y++;
		carte = carte->next;
	}
	mlx_put_image_to_window(mlx, win, put->img, 15, 15);
	mlx_destroy_image(mlx, put->img);
}
