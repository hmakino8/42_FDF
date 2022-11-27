/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiroaki <hiroaki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 19:08:02 by hmakino           #+#    #+#             */
/*   Updated: 2022/11/28 01:30:40 by hiroaki          ###   ########.fr       */
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
//# define MENU_BKG_COLOR 0x1E1E1E
#define MENU_BKG_COLOR 0x2F4F4F
# define MAIN_BKG_COLOR 0x222222

typedef struct s_matrix
{
	int		width;
	int		height;
	int		alloccnt;
	int		coord_infocnt;
	int		**coord;
	int		**color_code;
	char	*line;
	char	**elem;
	char	**coord_info;
}	t_matrix;

typedef struct s_pos
{
	int	x;
	int	y;
	int	z;
	int	x1;
	int	y1;
	int	z1;
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

typedef struct s_map
{
}	t_map;

typedef struct s_mlx
{
	void	*init;
	void	*win;
	void	*img;
	void	*data_addr;
	int		bpp;
	int		size_line;
	int		endian;
}	t_mlx;

typedef struct s_data
{
	t_pos		p;
	t_camera	cam;
	t_map		map;
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
