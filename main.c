/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdrouet <cdrouet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/05 09:53:37 by cdrouet           #+#    #+#             */
/*   Updated: 2016/02/11 15:07:35 by cdrouet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

int		esc_touch(int keycode, void *param)
{
	t_move	*par;

	par = (t_move*)param;
	if (keycode == esc)
	{
		mlx_destroy_window(par->omlx.mlx, par->omlx.win);
		exit(0);
	}
	if (keycode == left)
	{
		mlx_clear_window(par->omlx.mlx, par->omlx.win);
		par->start.x -= 3;
		affiche_carte(par->carte, par->omlx, par->angle, par->start);
	}
	if (keycode == right)
	{
		mlx_clear_window(par->omlx.mlx, par->omlx.win);
		par->start.x += 3;
		affiche_carte(par->carte, par->omlx, par->angle, par->start);
	}
	if (keycode == up)
	{
		mlx_clear_window(par->omlx.mlx, par->omlx.win);
		par->start.y -= 3;
		affiche_carte(par->carte, par->omlx, par->angle, par->start);
	}
	if (keycode == down)
	{
		mlx_clear_window(par->omlx.mlx, par->omlx.win);
		par->start.y += 3;
		affiche_carte(par->carte, par->omlx, par->angle, par->start);
	}
	if (keycode == moin)
	{
		mlx_clear_window(par->omlx.mlx, par->omlx.win);
		par->angle.x -= 3;
		affiche_carte(par->carte, par->omlx, par->angle, par->start);
	}
	if (keycode == plus)
	{
		mlx_clear_window(par->omlx.mlx, par->omlx.win);
		par->angle.x += 3;
		affiche_carte(par->carte, par->omlx, par->angle, par->start);
	}
	return (0);
}

t_file	*lst_file_new(char **val)
{
	t_file	*new;

	if ((new = (t_file*)malloc(sizeof(t_file))) == NULL)
		return (NULL);
	new->split = val;
	new->next = NULL;
	return (new);
}

t_file	*init_carte(t_file *carte, char *file, t_pts *mm)
{
	int		fd;
	char	*line;
	t_file	*ret;

	fd = open(file, O_RDONLY);
	(*mm).x = 0;
	ret = NULL;
	if (get_next_line(fd, &line) > 0)
	{
		ret = lst_file_new(ft_strsplit(line, ' '));
		if (do_char_len(ret->split) > (*mm).x)
			(*mm).x = do_char_len(ret->split);
		carte = ret;
	}
	while (get_next_line(fd, &line) > 0)
	{
		carte->next = lst_file_new(ft_strsplit(line, ' '));
		if (do_char_len(carte->next->split) > (*mm).x)
			(*mm).x = do_char_len(carte->next->split);
		free(line);
		carte = carte->next;
	}
	close(fd);
	return (ret);
}

int		main(int argc, char **argv)
{
	t_file	*carte;
	t_mlx	prout;
	t_pts	angle;
	t_pts	start;
	t_move	param;

	(void)argc;
	carte = NULL;
	carte = init_carte(carte, argv[1], &angle);
	prout.mlx = mlx_init();
	prout.win = mlx_new_window(prout.mlx, 1000, 1000, ft_strjoin("FDF - ", argv[1]));
	start.x = 400;
	start.y = 200;
	param.angle = angle;
	param.omlx = prout;
	param.carte = carte;
	param.start = start;
	affiche_carte(carte, prout, angle, start);
//	mlx_key_hook(prout.win, esc_touch, &param);
	mlx_hook(prout.win, 2, 0, esc_touch, &param);
	mlx_loop(prout.mlx);
	return (0);
}
