/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdrouet <cdrouet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/12 14:27:08 by cdrouet           #+#    #+#             */
/*   Updated: 2016/02/15 11:57:35 by cdrouet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	event_fleche(int keycode, t_move *par)
{
	if (keycode == LEFT)
	{
		mlx_clear_window(par->omlx.mlx, par->omlx.win);
		par->start.x -= 3;
		affiche_carte(*par);
	}
	if (keycode == RIGHT)
	{
		mlx_clear_window(par->omlx.mlx, par->omlx.win);
		par->start.x += 3;
		affiche_carte(*par);
	}
	if (keycode == UP)
	{
		mlx_clear_window(par->omlx.mlx, par->omlx.win);
		par->start.y -= 3;
		affiche_carte(*par);
	}
	if (keycode == DOWN)
	{
		mlx_clear_window(par->omlx.mlx, par->omlx.win);
		par->start.y += 3;
		affiche_carte(*par);
	}
}

void	event_plus_moin(int keycode, t_move *par)
{
	par->zoom += (keycode == PLUS) ? 1 : -1;
	mlx_clear_window(par->omlx.mlx, par->omlx.win);
	affiche_carte(*par);
}

void	initialise_affiche(t_move *param, t_pts *init, t_pts *dec, t_img **put)
{
	int		tempo;
	double	coef;
	double	t1;
	double	t2;

	if ((tempo = (*param).angle.x) > lst_len((*param).carte))
	{
		(*init).x = (600 / (*param).angle.x);
		(*init).y = (600 / (*param).angle.x);
	}
	else
	{
		(*init).x = 600 / lst_len((*param).carte);
		(*init).y = 600 / lst_len((*param).carte);
	}
	t1 = (double)(*init).x;
	t2 = (double)(((*param).angle.x > lst_len((*param).carte)) ?
		(*param).angle.x : lst_len((*param).carte));
	coef = t1 / t2;
	(*param).angle.x *= coef;
	(*param).angle.y = (*param).angle.x * 0.4;
	(*dec).x = (*param).start.x + ((*param).angle.x * lst_len((*param).carte));
	(*dec).y = (*param).start.y + ((*param).angle.y * tempo);
	(*put) = t_img_init((*param).omlx.mlx, 1600, 1000);
	(*put)->color = mlx_get_color_value((*param).omlx.mlx, 0xFFFFFF);
}

int		lst_len(t_file *lst)
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
