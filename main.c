/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdrouet <cdrouet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/05 09:53:37 by cdrouet           #+#    #+#             */
/*   Updated: 2016/02/11 08:47:49 by cdrouet          ###   ########.fr       */
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
	t_img	*put;
	t_pts	pt1;
	t_pts	pt2;

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
//	affiche_carte(carte, prout.mlx, prout.win, angle);
	put = t_img_init(prout.mlx, 900, 900);
	put->color = mlx_get_color_value(prout.mlx, 0x0000FF);
	pt1.x = 285;
	pt1.y = 140;
	pt2.x = 300;
	pt2.y = 100;
	trace_segment(pt1, pt2, put);
	mlx_put_image_to_window(prout.mlx, prout.win, put->img, 15, 15);
	mlx_destroy_image(prout.mlx, put->img);
	mlx_key_hook(prout.win, esc_touch, &param);
	mlx_loop(prout.mlx);
	return (0);
}
