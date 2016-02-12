/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   affiche.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdrouet <cdrouet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/10 08:14:01 by cdrouet           #+#    #+#             */
/*   Updated: 2016/02/12 11:51:34 by cdrouet          ###   ########.fr       */
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
	int		i;
	int		y;
	double	coef;
	double	t1;
	double	t2;
	t_pts	init;
	t_pts	dec;
	t_img	*put;

	if (param.angle.x > lst_len(param.carte))
	{
		init.x = 600 / param.angle.x;
		init.y = 600 / param.angle.x;
	}
	else
	{
		init.x = 600 / lst_len(param.carte);
		init.y = 600 / lst_len(param.carte);
	}
	t1 = (double)init.x;
	t2 = (double)((param.angle.x > lst_len(param.carte))?
		param.angle.x : lst_len(param.carte));
	coef = t1 / t2;
	param.angle.x *= (coef );
	param.angle.y = param.angle.x * 0.4;
	put = t_img_init(param.omlx.mlx, 1000, 1000);
	dec.x = param.start.x;
	dec.y = param.start.y;
	y = 0;
	put->color = mlx_get_color_value(param.omlx.mlx, 0xFFFFFF);
	while (param.carte)
	{
		i = 0;
		dec.y = param.start.y;
		while (param.carte->split[i])
		{
			if (param.carte->split[i + 1])
				trace_segment(decal(init_pts(init, i, y), dec.x,
					((dec.y - (param.zoom *
						ft_atoi(param.carte->split[i]))) / 2)),
							decal(init_pts(init, i + 1, y), dec.x,
								((dec.y + param.angle.y - (param.zoom *
									ft_atoi(param.carte->split[i + 1])))
										/ 2)), put);
			if (param.carte->next)
				if (i < do_char_len(param.carte->next->split))
					trace_segment(decal(init_pts(init, i, y), dec.x,
						((dec.y - (param.zoom *
							ft_atoi(param.carte->split[i]))) / 2)),
								decal(init_pts(init, i, y + 1),
									dec.x - param.angle.x, ((dec.y -
										(param.zoom * ft_atoi(
											param.carte->next->split[i])))
												/ 2)), put);
			i++;
			dec.y += param.angle.y;
		}
		dec.x -= param.angle.x;
		y++;
		param.carte = param.carte->next;
	}
	mlx_put_image_to_window(param.omlx.mlx, param.omlx.win, put->img, 0, 0);
	mlx_destroy_image(param.omlx.mlx, put->img);
}
