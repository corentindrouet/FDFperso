/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdrouet <cdrouet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/05 10:38:50 by cdrouet           #+#    #+#             */
/*   Updated: 2016/02/15 08:18:35 by cdrouet          ###   ########.fr       */
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

void				event_plus_moin(int keycode, t_move *par);
void				event_fleche(int keycode, t_move *par);
void				first_ca(t_pts d, t_pts start, t_pts stop, t_img *jpg);
void				second_ca(t_pts d, t_pts start, t_pts stop, t_img *jpg);
void				third_ca(t_pts d, t_pts start, t_pts stop, t_img *jpg);
void				last_ca(t_pts d, t_pts start, t_pts stop, t_img *jpg);
void				d_x_pos(t_pts d, t_pts start, t_pts stop, t_img *jpg);
void				d_x_neg(t_pts d, t_pts start, t_pts stop, t_img *jpg);
int					lst_len(t_file *lst);
int					do_char_len(char **str);
void				affiche_carte(t_move param);
void				initialise_affiche(t_move *param,
						t_pts *init, t_pts *dec, t_img **put);
t_file				*lst_file_new(char **val);
t_file				*init_carte(t_file *carte, char *file, t_pts *mm);
t_img				*t_img_init(void *mlx, int x, int y);
void				trace_segment(t_pts start, t_pts stop, t_img *jpg);
int					write_img(int x, int y, t_img *jpg);

#endif
