/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdrouet <cdrouet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/05 09:53:37 by cdrouet           #+#    #+#             */
/*   Updated: 2016/02/08 15:49:08 by cdrouet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		esc_touch(int keycode, void *param)
{
	t_mlx	*prout;

	if (keycode == esc)
	{
		prout = (t_mlx*)param;
		mlx_destroy_window(prout->mlx, prout->win);
		exit(0);
	}
	return (0);
}

t_file	*lst_new(char **val)
{
	t_file	*new;

	if ((new = (t_file*)malloc(sizeof(t_file))) == NULL)
		return (NULL);
	new->split = val;
	new->next = NULL;
	return (new);
}

void	init_carte(t_file *carte, char *file)
{
	int		i;
	int		fd;
	char	*line;

	fd = open(file, O_RDONLY);
	while (get_next_line(fd, &line) >= 0)
	{
		carte = lst_new(ft_strsplit(line));
		carte = carte->next;
	}
	close(fd);
}

int		main(int argc, char **argv)
{
	t_file	*carte;
	t_mlx	prout;
	t_img	*essai;
	t_pts	pt1;
	t_pts	pt2;

	carte = NULL;
	prout.mlx = mlx_init();
	prout.win = mlx_new_window(prout.mlx, 600, 600, "prout");
	essai = t_img_init(prout.mlx, 600, 600);
	pt1.x = 0;
	pt1.y = 0;
	pt2.x = 100;
	pt2.y = 0;
	essai->color = mlx_get_color_value(prout.mlx, 0x0000FF);
	trace_segment(pt1, pt2, essai);
	mlx_put_image_to_window(prout.mlx, prout.win, essai->img, 100, 100);
	mlx_destroy_image(prout.mlx, essai->img);
	mlx_key_hook(prout.win, esc_touch, &prout);
	mlx_loop(prout.mlx);
	return (0);
}
