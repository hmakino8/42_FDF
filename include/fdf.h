/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiroaki <hiroaki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 19:08:02 by hmakino           #+#    #+#             */
/*   Updated: 2022/12/02 21:46:53 by hiroaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <stdio.h>
# include <stdbool.h>
# include <math.h>
# include "../minilibx_macos/mlx.h"
# include "../libs/include/libft.h"
# include "../libs/include/ft_print.h"
# include "../libs/include/get_next_line.h"

/*
 * Output
 */
# define STD_OUT 1
# define STD_ERROR 2

/*
 * Width/Height
 */
# define SCR_HEIGHT 1080
# define SCR_WIDTH 1920
# define MENU_WIDTH 250

/*
 * Projection
 */
# define INIT 1
# define PARALLEL 2

/*
 * Color
 */
# define NO_COLOR 0x0
# define DEEPPINK 0xFF1493
# define INDIGO 0x165E83
# define BLACKDIAMOND 0x252A2D

/*
 * Direction key
 */
# define KEY_UP		126
# define KEY_DOWN	125
# define KEY_LEFT	123
# define KEY_RIGHT	124

/*
 * Main mum key
 */
# define KEY_0			29
# define KEY_1			18
# define KEY_2			19
# define KEY_3			20
# define KEY_4			21
# define KEY_5			23
# define KEY_6			22
# define KEY_7			26
# define KEY_8			28
# define KEY_9			25

/*
 * Main alphabet key
 */
# define KEY_A			0
# define KEY_E			14
# define KEY_S			1
# define KEY_D			2
# define KEY_F			3
# define KEY_H			4
# define KEY_I			34
# define KEY_J			38
# define KEY_K			40
# define KEY_L			37
# define KEY_R			15
# define KEY_P			35
# define KEY_U			32
# define KEY_W			13

/*
 * Main symbol key
 */
# define KEY_ESC		53
# define KEY_PLUS		24
# define KEY_MINUS		27
# define KEY_LESS		43
# define KEY_GRATER		47

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
	int				zoom;
	int				x_et;
	int				y_et;
	int				projection;
	double			alpha;
	double			beta;
	double			gamma;
	double			z_div;
}	t_camera;

typedef struct s_mlx
{
	int		bpp;
	int		endian;
	int		size_line;
	char	*data_addr;
	void	*win;
	void	*img;
	void	*init;
}	t_mlx;

typedef struct s_data
{
	t_pos		p;
	t_camera	cam;
	t_mlx		*mlx;
	t_matrix	*mx;
}	t_data;

/* * * * * * * *
 *   init dir  *
 * * * * * * * */

/* init.c */
void	init_fd(t_data *d, int *fd, char *filename);
void	init_axis(t_camera *cam);
void	init_s_mlx(t_data *d, t_mlx *mlx);
void	init_s_camera(t_camera *cam, t_matrix *mx);
void	init_s_matrix(t_matrix *mx);

/* * * * * * * *
 *  parse dir  *
 * * * * * * * */

/* get_matrix.c */
void	get_matrix(t_data *d, char *filename);
/* get_color_code.c */
void	get_color_code(t_data *d, t_matrix *mx, int i, int j);
/* get_coord.c */
void	get_coord(t_data *d, t_matrix *mx, int i, int j);
/* parse_coord_info.c */
void	parse_line(t_data *d, t_matrix *mx, int i);

/* * * * * * * *
 *   exit dir  *
 * * * * * * * */

/* exit.c */
void	free_all_struct(t_data *d);
void	free_all_array(t_matrix *mx);
void	fdf_exit(t_data *d, char *errmsg);
/* alloc.c */
void	alloc_arr(t_data *d, t_matrix *mx);
t_data	*alloc_s_data(void);

/* * * * * * * *
 *  color dir  *
 * * * * * * * */

/* color.c */
t_pos	get_original_color(t_data *d, t_pos p);
t_pos	get_menu_color(t_pos cur);
t_pos	get_color(t_pos st, t_pos cur, t_pos to, double rt);
double	get_color_ratio(t_pos delta, t_pos st, t_pos cur, t_pos to);

/* * * * * * * *
 * render dir  *
 * * * * * * * */

/* draw.c */
void	draw_line(t_data *d, t_pos p);
void	draw_colored_line(t_mlx *mlx, t_pos cur);
void	draw_bkg(t_mlx *mx);
/* render.c */
t_pos	reset_pos(t_data *d, t_pos p);
void	bresenham(t_data *d, t_pos st, t_pos to);
void	rendering(t_data *d, t_mlx *mlx, t_matrix *mx);
/* menu.c */
void	put_menu(t_mlx *mlx);

/* * * * * * * *
 *   key dir   *
 * * * * * * * */

/* key_hook.c */
void	key_hook(t_data *d, t_mlx *mlx);
/* operation_key.c */
int		zoom_key(t_camera *cam, int key);
int		move_key(t_camera *cam, int key);
int		rotate_key(t_camera *cam, int key);
int		projection_key(t_camera *cam, t_matrix *mx, int key);
int		adjust_depth_key(t_camera *cam, int key);

/* * * * * * * *
 *  utils dir  *
 * * * * * * * */

/* ft_atoi_base.c */
int		ft_atoi_base(char *str, int base, bool *ok);
/* ft_abs.c */
int		ft_abs(int diff);
/* ft_max.c */
int		ft_max(int a, int b);
/* ft_min.c */
int		ft_min(int a, int b);
/* check.c */
void	check_argc(t_data *d, int argc);
void	check_width(t_data *d, t_matrix *mx, int *width);

#endif
