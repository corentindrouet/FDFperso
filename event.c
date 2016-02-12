/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdrouet <cdrouet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/12 14:27:08 by cdrouet           #+#    #+#             */
/*   Updated: 2016/02/12 14:39:51 by cdrouet          ###   ########.fr       */
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

	tempo = (*param).angle.x;
}
