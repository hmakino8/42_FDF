/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiroaki <hiroaki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 02:08:05 by hiroaki           #+#    #+#             */
/*   Updated: 2022/11/26 04:00:02 by hiroaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"
#include <stdio.h>

void	fdf_exit(t_data *d, char *errmsg)
{
	free(d->m.coord);
	free(d->m.color);
	free(d->m.line);
	free_all_element((void **)d->elem, d->m.width);
	free_all_element((void **)d->m.info, d->elemcnt);
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

void	get_coord(t_data *d, int i)
{
	bool	ok;

	d->m.coord[i] = ft_atoi_base(d->m.info[0], 10, &ok);
	if (!ok)
		fdf_exit(d, "Invalid map coord.");
}

void	get_color_code(t_data *d, int i)
{
	bool	ok;

	if (d->elemcnt == 1)
		d->m.color[i] = ft_atoi_base(DEFAULT_COLOR, 16, &ok);
	if (ok && d->elemcnt == 2)
		d->m.color[i] = ft_atoi_base(d->m.info[1], 16, &ok);
	if (!ok)
		fdf_exit(d, "Invalid color code.");
}

void	get_info(t_data *d, int j)
{
	d->m.info = ft_split(d->elem[j], ',', &d->elemcnt);
	if (!d->m.info || d->elemcnt > 2)
		fdf_exit(d, "Failed to read map.");
}

void	parse_line(t_data *d, int i)
{
	int	j;

	j = -1;
	while (d->elem[++j])
	{
		get_info(d, j);
		get_coord(d, i);
		get_color_code(d, i);
		free_all_element((void **)d->m.info, d->elemcnt);
		d->m.info = NULL;
	}
}

void	alloc_arr(t_data *d, t_map *m)
{
	m->allocsize = m->height * m->width * sizeof(int);
	d->m.coord = (int *)malloc(m->allocsize);
	d->m.color = (int *)malloc(m->allocsize);
	if (!d->m.coord || !d->m.color)
		fdf_exit(d, "Malloc failure");
}

void	get_width(t_data *d, int fd)
{
	int	width;

	d->elem = ft_split(d->m.line, ' ', &width);
	if (!d->elem || (d->m.width && d->m.width != width))
		fdf_exit(d, "Failed to read map.");
	d->m.width = width;
}

void	get_height(t_data *d, int fd, int *signal)
{
	char	*gnl;

	gnl = get_next_line(fd, signal);
	d->m.line = ft_strtrim((const char *)gnl, "\n");
	if (*signal == END_OF_FILE)
		return ;
	if (!d->m.line)
		fdf_exit(d, "Failed to read file.");
	free(gnl);
	d->m.height++;
}

void	get_coord_info(t_data *d, char *filename)
{
	int		i;
	int		fd;
	int		signal;

	i = 0;
	init_fd(d, &fd, filename);
	while (1)
	{
		get_height(d, fd, &signal);
		if (signal == END_OF_FILE)
			break ;
		get_width(d, fd);
		if (d->m.height == 1)
			alloc_arr(d, &d->m);
		parse_line(d, i++);
		free(d->m.line);
		d->m.line = NULL;
	}
	close(fd);
}

void	get_map(t_data *d, char *filename)
{
	get_coord_info(d, filename);
}

void	init_data(t_data *d)
{
	d->m.width = 0;
	d->m.height = 0;
	d->elemcnt = 0;
	d->elem = NULL;
	d->m.line = NULL;
	d->m.coord = NULL;
	d->m.color = NULL;
	d->m.info = NULL;
}

int	main(int argc, char *argv[])
{
	t_data	d;

	init_data(&d);
	check_argc(&d, argc);
	get_map(&d, argv[1]);
}
