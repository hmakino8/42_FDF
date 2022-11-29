/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiroaki <hiroaki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 19:08:02 by hmakino           #+#    #+#             */
/*   Updated: 2022/11/30 03:30:43 by hiroaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <stdio.h>
# include <stdbool.h>
# include <math.h>
# include "../minilibx-linux/mlx.h"
# include "../libs/include/libft.h"
# include "../libs/include/ft_print.h"
# include "../libs/include/get_next_line.h"

# define STD_OUT 1
# define STD_ERROR 2
# define SCR_HEIGHT 1080
# define SCR_WIDTH 1920
# define MENU_WIDTH 250
# define DEFAULT_ANGLE 1
# define DARKORCHID 0x9932CC
# define ORANGERED 0xFF4500
# define BOTTOM_COLOR 0
# define TOP_COLOR 0xFF00FF
# define MAGENTA 0xFF00FF
# define MEDIUMPURPLE 0x9370DB
# define DEEPPINK 0xFF1493
# define LIME 0x00FF00
# define YELLOW 0xFFFF00
# define DARKGREEN 0x006400
# define DEEPSKYBLUE 0x00BFFF
# define MENU_BKG_COLOR 0x2F4F4F
# define MAIN_BKG_COLOR 0x222222
//# define MAIN_BKG_COLOR 0

	typedef struct s_matrix
{
	int		width;
	int		height;
	int		depth_max;
	int		depth_min;
	int		alloccnt;
	int		coord_infocnt;
	int		**coord;
	int		**color;
	char	*line;
	char	**elem;
	char	**coord_info;
}	t_matrix;

typedef struct s_color
{
	int		color;
	int		red;
	int		green;
	int		blue;
	bool	map_color;
}	t_color;

typedef struct s_pos
{
	int		x;
	int		y;
	int		z;
	t_color	c;
}	t_pos;

typedef struct s_camera
{
	int			zoom;
	int			x_et;
	int			y_et;
	double		alpha;
	double		beta;
	double		gamma;
	double		z_div;
}	t_camera;

typedef struct s_mlx
{
	void	*init;
	void	*win;
	void	*img;
	char	*data_addr;
	int		bpp;
	int		size_line;
	int		endian;
}	t_mlx;

typedef struct s_data
{
	t_pos		p;
	t_camera	cam;
	t_mlx		*mlx;
	t_matrix	*mx;
}	t_data;

/* * * * * * * *
 *   main dir  *
 * * * * * * * */

/* main.c */

/* * * * * * * *
 *  utils dir  *
 * * * * * * * */

/* ft_atoi_base.c */
int	ft_atoi_base(char *str, int base, bool *ok);

#endif
