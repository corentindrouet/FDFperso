/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdrouet <cdrouet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/05 09:53:37 by cdrouet           #+#    #+#             */
/*   Updated: 2016/02/10 14:43:28 by cdrouet          ###   ########.fr       */
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
//		par->angle.x++;
//		par->angle.y--;
		affiche_carte(par->carte, par->omlx.mlx, par->omlx.win, par->angle);
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

t_file	*init_carte(t_file *carte, char *file)
{
	int		i;
	int		fd;
	char	*line;
	t_file	*ret;

	fd = open(file, O_RDONLY);
	i = 0;
	ret = NULL;
	if (get_next_line(fd, &line) > 0)
	{
		ret = lst_file_new(ft_strsplit(line, ' '));
		carte = ret;
	}
	while (get_next_line(fd, &line) > 0)
	{
		carte->next = lst_file_new(ft_strsplit(line, ' '));
		carte->ind = i++;
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
	t_move	param;

	(void)argc;
	carte = NULL;
	carte = init_carte(carte, argv[1]);
	prout.mlx = mlx_init();
	prout.win = mlx_new_window(prout.mlx, 1000, 1000, ft_strjoin("FDF - ", argv[1]));
	angle.x = 15;
	angle.y = 10;
	param.angle = angle;
	param.omlx = prout;
	param.carte = carte;
	affiche_carte(carte, prout.mlx, prout.win, angle);
	mlx_key_hook(prout.win, esc_touch, &param);
	mlx_loop(prout.mlx);
	return (0);
}
