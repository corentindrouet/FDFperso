/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdrouet <cdrouet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/05 09:53:37 by cdrouet           #+#    #+#             */
/*   Updated: 2016/02/23 11:30:19 by cdrouet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

int			esc_touch(int keycode, void *param)
{
	t_move	*par;

	par = (t_move*)param;
	if (keycode == ESC)
	{
		mlx_destroy_window(par->omlx.mlx, par->omlx.win);
		exit(0);
	}
	if (keycode == LEFT || keycode == RIGHT
		|| keycode == UP || keycode == DOWN)
		event_fleche(keycode, par);
	if (keycode == MOIN || keycode == PLUS)
		event_plus_moin(keycode, par);
	if (keycode == ESP)
	{
		mlx_clear_window(par->omlx.mlx, par->omlx.win);
		par->start.x = 160;
		par->start.y = 100;
		par->zoom = 2;
		affiche_carte(*par);
	}
	return (0);
}

t_file		*lst_file_new(char **val)
{
	t_file	*new;

	if ((new = (t_file*)malloc(sizeof(t_file))) == NULL)
		return (NULL);
	new->split = val;
	new->next = NULL;
	return (new);
}

static int	error_msg(int err)
{
	if (err == -1)
	{
		ft_printf("can't read this file\n");
		exit(0);
	}
	if (err == 0)
	{
		ft_printf("fichier vide\n");
		exit(0);
	}
	return (err);
}

t_file		*init_carte(t_file *carte, char *file, t_pts *mm)
{
	int		fd;
	char	*line;
	t_file	*ret;

	fd = open(file, O_RDONLY);
	error_msg(fd);
	(*mm).x = 0;
	ret = NULL;
	if ((error_msg(get_next_line(fd, &line))) > 0)
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

int			main(int argc, char **argv)
{
	t_move	param;
	char	*name;

	(void)argc;
	param.carte = NULL;
	param.carte = init_carte(param.carte, argv[1], &(param.angle));
	param.omlx.mlx = mlx_init();
	name = ft_strjoin("FDF - ", argv[1]);
	param.omlx.win = mlx_new_window(param.omlx.mlx,
		1600, 1000, name);
	free(name);
	param.start.x = 160;
	param.start.y = 100;
	param.zoom = 2;
	affiche_carte(param);
	mlx_hook(param.omlx.win, 2, 0, esc_touch, &param);
	mlx_loop(param.omlx.mlx);
	return (0);
}
