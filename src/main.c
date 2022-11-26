/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiroaki <hiroaki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 02:08:05 by hiroaki           #+#    #+#             */
/*   Updated: 2022/11/26 22:01:54 by hiroaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	fdf_exit(t_data *d, t_map *m, char *errmsg)
{
	free(m->line);
	free_all_element((void **)m->coord, m->alloccnt);
	free_all_element((void **)m->color, m->alloccnt);
	free_all_element((void **)m->elem, m->width);
	free_all_element((void **)m->info, m->infocnt);
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
		fdf_exit(d, &d->m, "Invalid argument.");
}

void	init_fd(t_data *d, int *fd, char *filename)
{
	*fd = open(filename, O_RDONLY);
	if (fd <= 0)
		fdf_exit(d, &d->m, "Failed to open file.");
}

void	get_coord(t_data *d, t_map *m, int i, int j)
{
	bool	ok;

	m->coord[i][j] = ft_atoi_base(m->info[0], 10, &ok);
	if (!ok)
		fdf_exit(d, &d->m, "Invalid map coord.");
}

void	get_color_code(t_data *d, t_map *m, int i, int j)
{
	bool	ok;

	if (m->infocnt == 1)
		m->color[i][j] = ft_atoi_base(DEFAULT_COLOR, 16, &ok);
	if (ok && m->infocnt == 2)
		m->color[i][j] = ft_atoi_base(d->m.info[1], 16, &ok);
	if (!ok)
		fdf_exit(d, &d->m, "Invalid color code.");
}

void	get_coord_info(t_data *d, t_map *m, char *elem)
{
	m->info = ft_split(elem, ',', &m->infocnt);
	if (!m->info || m->infocnt > 2)
		fdf_exit(d, &d->m, "Failed to read map.");
}

void	parse_line(t_data *d, t_map *m, int i)
{
	int	j;

	j = -1;
	while (m->elem[++j])
	{
		get_coord_info(d, m, m->elem[j]);
		get_coord(d, m, i, j);
		get_color_code(d, m, i, j);
		free_all_element((void **)d->m.info, m->infocnt);
		d->m.info = NULL;
	}
}

void	alloc_arr(t_data *d, t_map *m)
{
	int	i;

	m->alloccnt = 0;
	m->coord = (int **)malloc(m->height * sizeof(int *));
	m->color = (int **)malloc(m->height * sizeof(int *));
	if (!m->coord || !m->color)
		fdf_exit(d, m, "Malloc failure");
	i = -1;
	while (++i < m->height)
	{
		m->coord[i] = (int *)malloc(m->width * sizeof(int));
		m->color[i] = (int *)malloc(m->width * sizeof(int));
		if (!m->coord[i] || !m->color[i])
			fdf_exit(d, m, "Malloc failure");
		m->alloccnt++;
	}
}

void	get_height(t_data *d, t_map *m, int *signal, int fd)
{
	m->line = get_next_line(fd, signal);
	if (*signal == END_OF_FILE)
	{
		free(m->line);
		m->line = NULL;
		return ;
	}
	if (!m->line)
		fdf_exit(d, m, "Failed to read map");
	m->height++;
}

void	get_width(t_data *d, t_map *m)
{
	int	width;

	ft_split(m->line, ' ', &width);
	free(m->line);
	m->line = NULL;
	if (!m->width)
		m->width = width;
	if (!width || m->width != width)
		fdf_exit(d, m, "Invalid width in map.");
}

void	get_range(t_data *d, t_map *m, char *filename)
{
	int	fd;
	int	signal;

	init_fd(d, &fd, filename);
	while (1)
	{
		get_height(d, m, &signal, fd);
		if (signal == END_OF_FILE)
			return ;
		get_width(d, m);
	}
	close(fd);
}

void	get_matrix(t_data *d, t_map *m, char *filename)
{
	int	fd;
	int	i;
	int	signal;

	init_fd(d, &fd, filename);
	i = -1;
	while (1)
	{
		m->line = ft_strtrim(get_next_line(fd, &signal), "\n");
		if (signal == END_OF_FILE)
			return ;
		m->elem = ft_split(m->line, ' ', &m->width);
		parse_line(d, m, ++i);
		if (!m->elem)
			fdf_exit(d, &d->m, "Failed to read map");
		free(m->line);
	}
	close(fd);
}

void	get_map(t_data *d, char *filename)
{
	int		fd;

	get_range(d, &d->m, filename);
	alloc_arr(d, &d->m);
	get_matrix(d, &d->m, filename);
}

int ft_abs(float diff)
{
	if (diff < 0)
		return (-diff);
	return (diff);
}

int	ft_max(float a, float b)
{
	if (a < b)
		return (b);
	return (a);
}

void	isometric(float *x, float *y, int z)
{
	*x = (*x - *y) * cos(0.8);
	*y = (*x + *y) * sin(0.8) - z;
}

//void	bresenham_algo(t_data *d, float x, float y, float x1, float y1)
//{
//	int		max;
//	float	x_step;
//	float	y_step;
//	int		z;
//	int		z1;
//
//	z = d->m.coord[(int)x + (int)y * d->m.width];
//	z1 = d->m.coord[(int)x1 + (int)y1 * d->m.width];
//	//x *= d->m.zoom;
//	//y *= d->m.zoom;
//	//x1 *= d->m.zoom;
//	//y1 *= d->m.zoom;
//	//z *= d->m.zoom;
//	//z1 *= d->m.zoom;
//	//isometric(&x, &y, z);
//	//isometric(&x1, &y1, z1);
//	//coord_update(d, &x, &y, &x1, &y1);
//	//x += 150;
//	//y += 150;
//	//x1 += 150;
//	//y1 += 150;
//	//x_step = ft_abs(x1 - x);
//	//y_step = ft_abs(y1 - y);
//	//max = ft_max(x_step, y_step);
//	//x_step /= max;
//	//y_step /= max;
//	//while ((int)(x - x1) || (int)(y - y1))
//	//{
//	//	//mlx_pixel_put(d->mlx.ptr, d->mlx.win_ptr, x, y, 255);
//	//	x += x_step;
//	//	y += y_step;
//	//}
//}

int	deal_key(int key, void *d)
{
	ft_printf("%d", key);
	return (0);
}

//void	fdf_rendering(t_data *d, t_map *m)
//{
//	float	x;
//	float	y;
//
//	y = 0;
//	while (y < d->m.height)
//	{
//		x = 0;
//		while (x < d->m.width)
//		{
//			if (x < d->m.width - 1)
//				bresenham_algo(d, x, y, x + 1, y);
//			//if (y < d->m.height - 1)
//			//	bresenham_algo(d, x, y, x, y + 1);
//			x++;
//		}
//		y++;
//	}
//}

//void	draw_map(t_data *d)
//{
//	//d->mlx.ptr = mlx_init();
//	//d->mlx.win_ptr = mlx_new_window(d->mlx.ptr, 1000, 1000, "FdF");
//	fdf_rendering(d, &d->m);
//	//mlx_key_hook(d->mlx.win_ptr, deal_key, NULL);
//	//mlx_loop(d->mlx.ptr);
//}

void	init_map_data(t_map *m)
{
	m->infocnt = 0;
	m->elem = NULL;
	m->width = 0;
	m->height = 0;
	m->zoom = 20;
	m->allocsize = 0;
	m->line = NULL;
	m->coord = NULL;
	m->color = NULL;
	m->info = NULL;
}

int	main(int argc, char *argv[])
{
	t_data	d;

	init_map_data(&d.m);
	check_argc(&d, argc);
	get_map(&d, argv[1]);
	//int i = -1;
	//while (++i < d.m.height)
	//{
	//	int j = -1;
	//	while (++j < d.m.width)
	//		printf("%3d",d.m.coord[i][j]);
	//	printf("\n");
	//}
	draw_map(&d);
	fdf_exit(&d, &d.m, NULL);
}
