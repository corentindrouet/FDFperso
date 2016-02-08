/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdrouet <cdrouet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/05 10:38:50 by cdrouet           #+#    #+#             */
/*   Updated: 2016/02/08 13:50:17 by cdrouet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include <mlx.h>
# include <stdlib.h>
# include "touch.h"

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
	unsigned long	color
	char			*ret;
}					t_img;

t_img				*t_img_init(void *mlx, int x, int y);
void				trace_segment(t_pts start, t_pts stop, t_img *jpg);
void				write_img(int x, int y, t_img jpg);

#endif
