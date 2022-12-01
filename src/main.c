/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiroaki <hiroaki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 02:08:05 by hiroaki           #+#    #+#             */
/*   Updated: 2022/12/02 01:30:45 by hiroaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

int	ft_max(int a, int b);
int	ft_min(int a, int b);
void	adjust_screen(t_camera *cam, t_matrix *mx);

void	free_all_struct(t_data *d)
{
	if (!d)
		return ;
	free(d->mx);
	free(d->mlx);
	free(d);
}

void	free_all_array(t_matrix *mx)
{
	free(mx->line);
	free_all_element((void **)mx->coord, mx->alloccnt);
	free_all_element((void **)mx->color, mx->alloccnt);
	free_all_element((void **)mx->elem, mx->width);
	free_all_element((void **)mx->coord_info, mx->coord_infocnt);
}

void	fdf_exit(t_data *d, char *errmsg)
{
	free_all_array(d->mx);
	free_all_struct(d);
	if (errmsg)
	{
		ft_dprintf(STD_ERROR, "%s\n", errmsg);
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}

void	check_argc(t_data *d, int argc)
{
	if (argc < 2)
		fdf_exit(d, "Invalid argument.");
}

void	init_fd(t_data *d, int *fd, char *filename)
{
	*fd = open(filename, O_RDONLY);
	if (fd <= 0)
		fdf_exit(d, "Failed to open file.");
}

void	get_coord(t_data *d, t_matrix *mx, int i, int j)
{
	bool	ok;

	mx->coord[i][j] = ft_atoi_base(mx->coord_info[0], 10, &ok);
	if (!ok)
		fdf_exit(d, "Invalid map coord.");
	mx->depth_max = ft_max(mx->depth_max, mx->coord[i][j]);
	mx->depth_min = ft_min(mx->depth_min, mx->coord[i][j]);
}

void	get_color_code(t_data *d, t_matrix *mx, int i, int j)
{
	bool	ok;

	ok = false;
	if (mx->coord_infocnt == 1)
		mx->color[i][j] = -1;
	if (mx->coord_infocnt == 2)
		mx->color[i][j] = ft_atoi_base(mx->coord_info[1], 16, &ok);
	if (mx->coord_infocnt != 1 && !ok)
		fdf_exit(d, "Invalid color code.");
}

void	get_coord_info(t_data *d, t_matrix *mx, char *elem)
{
	mx->coord_info = ft_split(elem, ',', &mx->coord_infocnt);
	if (!mx->coord_info || mx->coord_infocnt > 2)
		fdf_exit(d, "Failed to read map.");
}

void	parse_line(t_data *d, t_matrix *mx, int i)
{
	int	j;

	j = -1;
	while (mx->elem[++j])
	{
		get_coord_info(d, mx, mx->elem[j]);
		get_coord(d, mx, i, j);
		get_color_code(d, mx, i, j);
		free_all_element((void **)mx->coord_info, mx->coord_infocnt);
		mx->coord_info = NULL;
	}
}

void	alloc_arr(t_data *d, t_matrix *mx)
{
	int	i;

	mx->alloccnt = 0;
	mx->coord = (int **)malloc(mx->height * sizeof(int *));
	mx->color = (int **)malloc(mx->height * sizeof(int *));
	if (!mx->coord || !mx->color)
		fdf_exit(d, "Malloc failure");
	i = -1;
	while (++i < mx->height)
	{
		mx->coord[i] = (int *)malloc(mx->width * sizeof(int));
		mx->color[i] = (int *)malloc(mx->width * sizeof(int));
		if (!mx->coord[i] || !mx->color[i])
			fdf_exit(d, "Malloc failure");
		mx->alloccnt++;
	}
}

void	get_height(t_data *d, t_matrix *mx, int *signal, int fd)
{
	mx->line = get_next_line(fd, signal);
	if (*signal == END_OF_FILE)
	{
		free(mx->line);
		mx->line = NULL;
		return ;
	}
	if (!mx->line)
		fdf_exit(d, "Failed to read map");
	mx->height++;
}

void	get_width(t_data *d, t_matrix *mx)
{
	int	width;

	ft_split(mx->line, ' ', &width);
	free(mx->line);
	mx->line = NULL;
	if (!mx->width)
		mx->width = width;
	else
		mx->width = ft_max(mx->width, width);
}

void	get_range(t_data *d, char *filename)
{
	int	fd;
	int	signal;

	init_fd(d, &fd, filename);
	while (1)
	{
		get_height(d, d->mx, &signal, fd);
		if (signal == END_OF_FILE)
			return ;
		get_width(d, d->mx);
	}
	close(fd);
}

void	check_width(t_data *d, t_matrix *mx, int *width)
{
	if (!*width)
		*width = mx->width;
	else if (mx->width != *width)
		fdf_exit(d, "Invalid width in map.");
}

void	init_matrix(t_data *d, t_matrix *mx, char *filename)
{
	int	i;
	int	fd;
	int	width;
	int	signal;

	init_fd(d, &fd, filename);
	width = 0;
	i = -1;
	while (1)
	{
		mx->line = ft_strtrim(get_next_line(fd, &signal), "\n ");
		if (signal == END_OF_FILE)
			return ;
		mx->elem = ft_split(mx->line, ' ', &mx->width);
		check_width(d, mx, &width);
		if (!mx->elem)
			fdf_exit(d, "Failed to read map");
		parse_line(d, mx, ++i);
		free(mx->line);
	}
	close(fd);
}

void	get_matrix(t_data *d, char *filename)
{
	int	fd;

	get_range(d, filename);
	alloc_arr(d, d->mx);
	init_matrix(d, d->mx, filename);
}

int ft_abs(int diff)
{
	if (diff < 0)
		return (-diff);
	return (diff);
}

int	ft_max(int a, int b)
{
	if (a < b)
		return (b);
	return (a);
}

int	ft_min(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}

void	draw_colored_line(t_mlx *mlx, t_matrix *mx, t_camera *cam, t_pos cur)
{
	int	i;

	if (cur.x >= MENU_WIDTH && cur.x < SCR_WIDTH && \
		cur.y >= 0 && cur.y < SCR_HEIGHT)
	{
		cam->eg.left = ft_min(cam->eg.left, cur.x);
		cam->eg.right = ft_max(cam->eg.right, cur.x);
		cam->eg.upper = ft_max(cam->eg.upper, cur.y);
		cam->eg.lower = ft_min(cam->eg.lower, cur.y);
		i = (cur.x * mlx->bpp / 8) + (cur.y * mlx->size_line);
		mlx->data_addr[i] = cur.c.color;
		mlx->data_addr[++i] = (int)cur.c.color >> 8;
		mlx->data_addr[++i] = (int)cur.c.color >> 16;
	}
}

void my_mlx_pixel_put(t_mlx *data, int x, int y, int color)
{
	char	*dst;

	dst = data->data_addr + (y * data->size_line + x * (data->bpp / 8));
	*(unsigned int *)dst = color;
}

/*
 * Δx = |x`-x| => 次のpixelまでのx軸方向の距離
 * Δy = |y`-y| => 次のpixelまでのy軸方向の距離
 * k = Δy/Δx   => (x, y)から(x`, y`)の直線の傾き
 *
 *            error[i-1]+k       (error[i-1] < 0.5)
 * error[i] { error[i-1]+k-1     (error[i-1] >= 0.5) => 誤差(実数)
 *
 * 実数k,0.5を整数として扱いたいので両辺を2Δx倍(2Δx * error[i] => error[i]`)
 *             error[i-1]`+2Δy        (error[i-1]` >= Δx)
 * error[i]` { error[i-1]`+2Δy-2Δx    (error[i-1]` >= Δx) => 誤差(整数)
 */

t_pos	relocate_pos(int error[], t_pos cur, t_pos delta, t_pos sign)
{
	error[1] = error[0] * 2;
	if (error[1] > -delta.y)
	{
		error[0] -= delta.y;
		cur.x += sign.x;
	}
	if (error[1] < delta.x)
	{
		error[0] += delta.x;
		cur.y += sign.y;
	}
	return (cur);
}

double	get_color_ratio(t_pos delta, t_pos st, t_pos cur, t_pos to)
{
	double	ratio;

	if (!(to.x - st.x) || !(to.y - st.y))
		return (1.0);
	if (delta.x > delta.y)
		ratio = (double)(cur.x - st.x) / (to.x - st.x);
	else
		ratio = (double)(cur.y - st.y) / (to.y - st.y);
	return (ratio);
}

t_pos	get_color(t_pos st, t_pos cur, t_pos to, double ratio)
{
	int		sc;
	int		tc;

	sc = st.c.color;
	tc = to.c.color;
	cur.c.red = (sc >> 16 & 0xFF) * (1 - ratio) + (tc >> 16 & 0xFF) * ratio;
	cur.c.green = (sc >> 8 & 0xFF) * (1 - ratio) + (tc >> 8 & 0xFF) * ratio;
	cur.c.blue = (sc & 0xFF) * (1 - ratio) + (tc & 0xFF) * ratio;
	cur.c.color = (cur.c.red << 16 | (cur.c.green << 8) | cur.c.blue);
	return (cur);
}

void	bresenham(t_data *d, t_pos st, t_pos to)
{
	t_pos	cur;
	t_pos	delta;
	t_pos	sign;
	double	ratio;
	int		error[2];

	delta.x = ft_abs(to.x - st.x);
	delta.y = ft_abs(to.y - st.y);
	sign.x = (st.x < to.x) - (st.x >= to.x);
	sign.y = (st.y < to.y) - (st.y >= to.y);
	error[0] = delta.x - delta.y;
	cur = st;
	while (cur.x != to.x || cur.y != to.y)
	{
		if (!cur.c.map_color && cur.c.color != to.c.color)
		{
			ratio = get_color_ratio(delta, st, cur, to);
			cur = get_color(st, cur, to, ratio);
		}
		draw_colored_line(d->mlx, d->mx, &d->cam, cur);
		cur = relocate_pos(error, cur, delta, sign);
	}
}

int	deal_key(int key, void *d)
{
	ft_printf("%d", key);
	return (0);
}

void	draw_bkg(t_mlx *mx)
{
	int	i;
	int	j;
	int	size;
	int	*img;

	size = SCR_WIDTH * SCR_HEIGHT * mx->bpp / 8;
	ft_bzero(mx->data_addr, size);
	img = (int *)mx->data_addr;
	i = -1;
	while (++i < SCR_WIDTH * SCR_HEIGHT)
	{
		j = i % SCR_WIDTH;
		if (j < MENU_WIDTH)
			img[i] = DARKGRAY;
		else
			img[i] = DARKGRAY;
	}
}

t_pos	rotate(t_camera *cam, t_pos p)
{
	double	prev_x;
	double	prev_y;

	if (cam->init)
	{
		prev_x = p.x;
		prev_y = p.y;
		p.x = (prev_x - prev_y) * cos(0.523599);
		p.y = -p.z + (prev_x + prev_y) * sin(0.523599);
	}
	else
	{
		prev_y = p.y;
		p.y = prev_y * cos(cam->alpha) + p.z * sin(cam->alpha);
		p.z = -prev_y * sin(cam->alpha) + p.z * cos(cam->alpha);
		prev_x = p.x;
		p.x = prev_x * cos(cam->beta) + p.z * sin(cam->beta);
		p.z = -prev_x * sin(cam->beta) + p.z * cos(cam->beta);
		prev_x = p.x;
		prev_y = p.y;
		p.x = prev_x * cos(cam->gamma) - prev_y * sin(cam->gamma);
		p.y = prev_x * sin(cam->gamma) - prev_y * cos(cam->gamma);
	}
	return (p);
}

//t_pos	depth_color(int z_max, int z_min, t_pos p, double ratio)
//{
//	t_pos	top;
//	t_pos	btm;
//
//	if (p.z >= 0)
//	{
//		top.c.color = DEEPPINK;
//		btm.c.color = INDIGO;
//	}
//	else
//	{
//		//top.c.color = INDIGO;
//		btm.c.color = BLACKDIAMOND;
//	}
//	if (p.z == z_max)
//		p.c.color = top.c.color;
//	else if (p.z == z_min)
//		p.c.color = btm.c.color;
//	else
//		return (get_color(btm, p, top, ratio));
//	return (p);
//}

int depth_gradation(t_pos p)
{
	if (p.z > 100)
		return (0xFFDF8D);
	if (p.z > 75)
		return (0xFFDE7A);
	if (p.z > 50)
		return (0xFFC568);
	if (p.z > 25)
		return (0xFD996B);
	if (p.z > 15)
		return (0xF7856C);
	if (p.z > 10)
		return (0xF06E6C);
	if (p.z > 5)
		return (0xD9576B);
	if (p.z > 0)
		return (0xA44369);
	if (p.z > -10)
		return (0x833F68);
	if (p.z > -20)
		return (0x833F68);
	if (p.z > -50)
		return (0x5E3C65);
	return (0x3F3A63);
}

t_pos	get_original_color(t_data *d, t_pos p)
{
	int		z_min;
	int		z_max;
	double	ratio;
	t_pos	top;
	t_pos	btm;

	z_max = d->mx->depth_max;
	z_min = d->mx->depth_min;
	top.c.color = DEEPPINK;
	btm.c.color = INDIGO;
	ratio = (double)(p.z - z_min) / (z_max - z_min);
	if (z_min > -20)
	{
		if (p.z == z_max)
			p.c.color = top.c.color;
		else if (p.z == z_min)
			p.c.color = btm.c.color;
		else
			p = get_color(btm, p, top, ratio);
	}
	else
		p.c.color = depth_gradation(p);
	return (p);
}

t_pos	reset_pos(t_data *d, t_pos p)
{
	p.c.color = d->mx->color[p.y][p.x];
	p.z = d->mx->coord[p.y][p.x];
	if (p.c.color < 0)
	{
		p.c.map_color = false;
		p = get_original_color(d, p);
	}
	else
		p.c.map_color = true;
	p.x *= d->cam.zoom;
	p.y *= d->cam.zoom;
	p.z *= d->cam.zoom * d->cam.z_div;
	p.x -= (d->mx->width * d->cam.zoom) / 2;
	p.y -= (d->mx->height * d->cam.zoom) / 2;
	p = rotate(&d->cam, p);
	p.x += SCR_WIDTH / 2 + d->cam.x_et;
	p.y += (SCR_HEIGHT + d->mx->height * d->cam.zoom) / 2 + d->cam.y_et;
	return (p);
}

void	draw_line(t_data *d, t_pos p)
{
	t_pos	st;
	t_pos	cur;

	st = p;
	cur = p;
	if (cur.x != d->mx->width - 1)
	{
		st.x++;
		bresenham(d, reset_pos(d, cur), reset_pos(d, st));
		st.x--;
	}
	if (cur.y != d->mx->height - 1)
	{
		st.y++;
		bresenham(d, reset_pos(d, cur), reset_pos(d, st));
	}
}

void	put_menu(t_mlx *mlx)
{
	mlx_string_put(mlx->init, mlx->win, 3, 60, 0xB0E0E6, \
	"    U S A G E    ");
	mlx_string_put(mlx->init, mlx->win, 3, 90, 0xE6E6FA, \
	"zoom *------- \'+\'");
}

void	rendering(t_data *d, t_mlx *mlx, t_matrix *mx)
{
	t_pos	p;

	draw_bkg(d->mlx);
	p.y = -1;
	while (++p.y < mx->height)
	{
		p.x = -1;
		while (++p.x < mx->width)
		{
			if (p.x != mx->width -1 || p.y != mx->height - 1)
				draw_line(d, p);
		}
	}
	mlx_put_image_to_window(mlx->init, mlx->win, mlx->img, 0, 0);
	put_menu(mlx);
}

void	init_s_mlx(t_data *d, t_mlx *mlx)
{
	mlx->win = NULL;
	mlx->img = NULL;
	mlx->data_addr = NULL;
	mlx->init = mlx_init();
	mlx->win = mlx_new_window(mlx->init, SCR_WIDTH, SCR_HEIGHT, "FdF");
	mlx->img = mlx_new_image(mlx->init, SCR_WIDTH, SCR_HEIGHT);
	mlx->data_addr = \
	mlx_get_data_addr(mlx->img, &mlx->bpp, &mlx->size_line, &mlx->endian);
	if (!mlx->init || !mlx->win || !mlx->img || !mlx->data_addr)
	{
		free(mlx->init);
		free(mlx->win);
		free(mlx->img);
		free(mlx->data_addr);
		fdf_exit(d, "Malloc Failure");
	}
}

void	init_s_camera(t_camera *cam, t_matrix *mx)
{
	int	width_ratio;
	int	height_ratio;

	width_ratio = SCR_WIDTH / mx->width / 2;
	height_ratio = SCR_HEIGHT / mx->height / 2;
	cam->zoom = ft_min(width_ratio, height_ratio) + 1;
	cam->init = true;
	cam->alpha = 0;
	cam->beta = 0;
	cam->gamma = 0;
	cam->x_et = 0;
	if (mx->depth_max > 50)
	{
		cam->y_et = -450;
		cam->z_div = 0.08;
	}
	else
	{
		cam->y_et = -100;
		cam->z_div = 0.8;
	}
}

void	init_s_matrix(t_matrix *mx)
{
	mx->width = 0;
	mx->height = 0;
	mx->depth_max = INT_MIN;
	mx->depth_min = INT_MAX;
	mx->coord_infocnt = 0;
	mx->elem = NULL;
	mx->line = NULL;
	mx->coord = NULL;
	mx->color = NULL;
	mx->coord_info = NULL;
}

t_data	*alloc_s_data(void)
{
	t_data	*d;

	d = (t_data *)malloc(sizeof(t_data));
	if (d)
	{
		d->mx = (t_matrix *)malloc(sizeof(t_matrix));
		d->mlx = (t_mlx *)malloc(sizeof(t_mlx));
	}
	if (!d || !d->mx || !d->mlx)
	{
		free_all_struct(d);
		ft_dprintf(2, "Malloc Failure\n");
		exit(EXIT_FAILURE);
	}
	return (d);
}

int	main(int argc, char *argv[])
{
	t_data		*d;

	d = alloc_s_data();
	init_s_matrix(d->mx);
	check_argc(d, argc);
	get_matrix(d, argv[1]);
	init_s_camera(&d->cam, d->mx);
	init_s_mlx(d, d->mlx);
	rendering(d, d->mlx, d->mx);
	mlx_loop(d->mlx->init);
	fdf_exit(d, NULL);
}
