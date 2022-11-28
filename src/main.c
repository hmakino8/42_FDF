/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiroaki <hiroaki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 02:08:05 by hiroaki           #+#    #+#             */
/*   Updated: 2022/11/28 17:31:16 by hiroaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

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
	free_all_element((void **)mx->color_code, mx->alloccnt);
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
}

void	get_color_code(t_data *d, t_matrix *mx, int i, int j)
{
	bool	ok;

	ok = false;
	if (mx->coord_infocnt == 1)
		mx->color_code[i][j] = -1;
	if (mx->coord_infocnt == 2)
		mx->color_code[i][j] = ft_atoi_base(mx->coord_info[1], 16, &ok);
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
	mx->color_code = (int **)malloc(mx->height * sizeof(int *));
	if (!mx->coord || !mx->color_code)
		fdf_exit(d, "Malloc failure");
	i = -1;
	while (++i < mx->height)
	{
		mx->coord[i] = (int *)malloc(mx->width * sizeof(int));
		mx->color_code[i] = (int *)malloc(mx->width * sizeof(int));
		if (!mx->coord[i] || !mx->color_code[i])
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
	if (!width || mx->width != width)
		fdf_exit(d, "Invalid width in map.");
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

void	init_matrix(t_data *d, t_matrix *mx, char *filename)
{
	int	i;
	int	fd;
	int	signal;

	init_fd(d, &fd, filename);
	i = -1;
	while (1)
	{
		mx->line = ft_strtrim(get_next_line(fd, &signal), "\n");
		if (signal == END_OF_FILE)
			return ;
		mx->elem = ft_split(mx->line, ' ', &mx->width);
		parse_line(d, mx, ++i);
		if (!mx->elem)
			fdf_exit(d, "Failed to read map");
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

void	draw_colored_line(t_mlx *mlx, t_pos cur, t_pos delta, t_pos sign)
{
	int	i;

	if (cur.x >= MENU_WIDTH && cur.x < SCR_WIDTH && \
		cur.y >= 0 && cur.y < SCR_HEIGHT)
	{
		i = (cur.x * mlx->bpp / 8) + (cur.y * mlx->size_line);
		mlx->data_addr[i] = 0x4E;
		mlx->data_addr[++i] = 0x1E;
		mlx->data_addr[++i] = 0x4F;
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

void	bresenham(t_mlx *mlx, t_pos cur, t_pos to)
{
	t_pos	delta;
	t_pos	sign;
	int		error[2];

	delta.x = ft_abs(to.x - cur.x);
	delta.y = ft_abs(to.y - cur.y);
	sign.x = (cur.x < to.x) - (cur.x >= to.x);
	sign.y = (cur.y < to.y) - (cur.y >= to.y);
	error[0] = delta.x - delta.y;
	while (cur.x != to.x || cur.y != to.y)
	{
		draw_colored_line(mlx, cur, delta, sign);
		//my_mlx_pixel_put(mlx, cur.x, cur.y, 0x00FF0000);
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
			img[i] = MENU_BKG_COLOR;
		else
			img[i] = MAIN_BKG_COLOR;
	}
}

t_pos	rotate(t_camera *cam, t_pos p)
{
	double	prev_x;
	double	prev_y;

	//prev_y = p.y;
	//p.y = prev_y * cos(cam->alpha) + p.z * sin(cam->alpha);
	//p.z = -prev_y * sin(cam->alpha) + p.z * cos(cam->alpha);

	//prev_x = p.x;
	//p.x = prev_x * cos(cam->beta) + p.z * sin(cam->beta);
	//p.z = -prev_x * sin(cam->beta) + p.z * cos(cam->beta);

	prev_x = p.x;
	prev_y = p.y;
	//p.x = prev_x * cos(cam->gamma) - prev_y * sin(cam->gamma);
	//p.y = prev_x * sin(cam->gamma) - prev_y * cos(cam->gamma);
	p.x = (prev_x - prev_y) * cos(0.523599);
	p.y = -p.z + (prev_x + prev_y) * sin(0.523599);
	return (p);
}

t_pos	pos(t_matrix *mx, t_camera *cam, t_pos p)
{
	p.z = mx->coord[p.y][p.x];
	p.x *= cam->zoom;
	p.y *= cam->zoom;
	p.z *= cam->zoom * cam->z_div;
	p.x -= (mx->width * cam->zoom) / 2;
	p.y -= (mx->height * cam->zoom) / 2;
	p = rotate(cam, p);
	p.x += (SCR_WIDTH - MENU_WIDTH) / 2 + cam->x_et + MENU_WIDTH;
	p.y += (SCR_HEIGHT + mx->height * cam->zoom) / 2 + cam->y_et;
	return (p);
}

void	draw_line(t_data *d, t_matrix *mx, t_pos cur, t_pos to)
{
	if (cur.x != mx->width - 1)
	{
		to.x++;
		bresenham(d->mlx, pos(mx, &d->cam, cur), pos(mx, &d->cam, to));
		to.x--;
	}
	if (cur.y != mx->height - 1)
	{
		to.y++;
		bresenham(d->mlx, pos(mx, &d->cam, cur), pos(mx, &d->cam, to));
	}
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
				draw_line(d, mx, p, p);
		}
	}
	mlx_put_image_to_window(mlx->init, mlx->win, mlx->img, 0, 0);
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

void	init_s_camera(int map_width, int map_height, t_camera *cam)
{
	int	width_ratio;
	int	height_ratio;

	width_ratio = (SCR_WIDTH - MENU_WIDTH) / map_width / 2;
	height_ratio = SCR_HEIGHT / map_height / 2;
	cam->zoom = ft_min(width_ratio, height_ratio);
	cam->alpha = 0;
	cam->beta = 0;
	cam->gamma = 0;
	cam->z_div = 1;
	cam->x_et = 0;
	cam->y_et = 0;
}

void	init_s_matrix(t_matrix *mx)
{
	mx->width = 0;
	mx->height = 0;
	mx->coord_infocnt = 0;
	mx->elem = NULL;
	mx->line = NULL;
	mx->coord = NULL;
	mx->color_code = NULL;
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
	init_s_mlx(d, d->mlx);
	init_s_camera(d->mx->width, d->mx->height, &d->cam);
	rendering(d, d->mlx, d->mx);
	mlx_loop(d->mlx->init);
	fdf_exit(d, NULL);
}
