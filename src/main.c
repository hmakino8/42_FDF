/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiroaki <hiroaki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 02:08:05 by hiroaki           #+#    #+#             */
/*   Updated: 2022/11/25 23:45:31 by hiroaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"
#include <stdio.h>

void	fdf_exit(t_data *d, char *errmsg)
{
	free_all_element((void **)d->m.coord, d->m.allocsize);
	free_all_element((void **)d->m.color, d->m.allocsize);
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

void	get_width(t_data *d, int fd, char *line)
{
	int	width;

	d->elem = ft_split(line, ' ', &width);
	if (!d->elem || (d->m.width && d->m.width != width))
	{
		d->m.width = width;
		fdf_exit(d, "Failed to read map.");
	}
	d->m.width = width;
}

void	parse_line(t_data *d, int i)
{
	int		j;
	bool	ok;

	j = -1;
	while (d->elem[++j])
	{
		d->m.info = ft_split(d->elem[j], ',', &d->elemcnt);
		if (!d->m.info || d->elemcnt > 2)
			fdf_exit(d, "Failed to read map.");
		d->m.coord[i] = ft_atoi_base(d->m.info[0], 10, &ok);
		if (d->elemcnt == 1)
			d->m.color[i] = ft_atoi_base(DEFAULT_COLOR, 16, &ok);
		if (ok && d->elemcnt == 2)
			d->m.color[i] = ft_atoi_base(d->m.info[1], 16, &ok);
		if (!ok)
			fdf_exit(d, "Invalid coord value or color code.");
		printf("%d ", d->m.color[i]);
		//free_all_element((void **)d->m.info, d->elemcnt);
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

void	get_coord_info(t_data *d, char *filename)
{
	int		i;
	int		fd;
	int		signal;
	char	*line;

	i = 0;
	init_fd(d, &fd, filename);
	while (1)
	{
		line = get_next_line(fd, &signal);
		if (!line && signal == END_OF_FILE)
			break ;
		else if (!line)
			fdf_exit(d, "Failed to read file.");
		d->m.height++;
		get_width(d, fd, line);
		if (!d->m.coord || !d->m.color)
			alloc_arr(d, &d->m);
		parse_line(d, i++);
		free(line);
		line = NULL;
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
