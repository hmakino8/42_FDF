/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_matrix.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiroaki <hiroaki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 02:08:05 by hiroaki           #+#    #+#             */
/*   Updated: 2022/12/07 14:18:41 by hiroaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/fdf.h"

static void	get_height(t_data *d, t_matrix *mx, int *signal, int fd)
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
	free(mx->line);
	mx->line = NULL;
}

static void	get_width(t_matrix *mx)
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

static void	get_range(t_data *d, char *filename)
{
	int	fd;
	int	signal;

	init_fd(d, &fd, filename);
	while (1)
	{
		get_height(d, d->mx, &signal, fd);
		if (signal == END_OF_FILE)
			return ;
		get_width(d->mx);
	}
	close(fd);
}

static void	init_matrix(t_data *d, t_matrix *mx, char *filename)
{
	int	i;
	int	fd;
	int	width;
	int	signal;
	char *gnl;

	init_fd(d, &fd, filename);
	width = 0;
	i = -1;
	while (1)
	{
		gnl = get_next_line(fd, &signal);
		mx->line = ft_strtrim(gnl, "\n ");
		free(gnl);
		if (signal == END_OF_FILE)
			return ;
		mx->elem = ft_split(mx->line, ' ', &mx->width);
		check_width(d, mx, &width);
		if (!mx->elem)
			fdf_exit(d, "Failed to read map");
		parse_line(d, mx, ++i);
		free(mx->line);
		mx->line = NULL;
	}
	close(fd);
}

void	get_matrix(t_data *d, char *filename)
{
	get_range(d, filename);
	alloc_arr(d, d->mx);
	init_matrix(d, d->mx, filename);
}
