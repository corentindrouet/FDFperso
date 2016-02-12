/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdrouet <cdrouet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/05 10:38:50 by cdrouet           #+#    #+#             */
/*   Updated: 2016/02/12 09:09:03 by cdrouet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include <mlx.h>
# include <stdlib.h>
# include "touch.h"
# include "libft/libft.h"
# include <fcntl.h>

typedef struct		s_file
{
	char			**split;
	struct s_file	*next;
}					t_file;

typedef struct		s_mlx
{
	void			*mlx;
	void			*win;
}					t_mlx;

typedef struct		s_pts
{
	int				x;
	int				y;
}					t_pts;

typedef struct		s_img
{
	void			*img;
	int				bits;
	int				sl;
	int				endian;
	unsigned long	color;
	t_pts			coord;
	char			*ret;
}					t_img;

typedef struct		s_move
{
	t_pts			angle;
	t_pts			start;
	t_mlx			omlx;
	t_file			*carte;
	int				zoom;
}					t_move;

int					lst_len(t_file *lst);
int					do_char_len(char **str);
void				affiche_carte(t_move param);
t_file				*lst_file_new(char **val);
t_file				*init_carte(t_file *carte, char *file, t_pts *mm);
t_img				*t_img_init(void *mlx, int x, int y);
void				trace_segment(t_pts start, t_pts stop, t_img *jpg);
int					write_img(int x, int y, t_img *jpg);

#endif
