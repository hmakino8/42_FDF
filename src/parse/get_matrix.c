/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_matrix.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiroaki <hiroaki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 02:08:05 by hiroaki           #+#    #+#             */
/*   Updated: 2022/12/10 14:33:16 by hiroaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/fdf.h"

static void	get_height(t_data *d, t_matrix *mx, int *signal, int fd)
{
	mx->gnl = get_next_line(fd, signal);
	mx->line = ft_strtrim(mx->gnl, "\n ");
	free(mx->gnl);
	if (*signal == END_OF_FILE)
	{
		free(mx->line);
		mx->line = NULL;
		return ;
	}
	if (!mx->line)
		fdf_exit(d, "Failed to read map.");
	mx->height++;
}

static void	get_width(t_data *d, t_matrix *mx)
{
	int	width;

	width = 0;
	free_all_element((void **)ft_split(mx->line, ' ', &width), width);
	free(mx->line);
	mx->line = NULL;
	check_width(d, mx, width);
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
		get_width(d, d->mx);
	}
	close(fd);
}

static void	init_matrix(t_data *d, t_matrix *mx, char *filename)
{
	int	i;
	int	fd;
	int	damy;
	int	signal;

	init_fd(d, &fd, filename);
	i = -1;
	while (1)
	{
		mx->gnl = get_next_line(fd, &signal);
		mx->line = ft_strtrim(mx->gnl, "\n ");
		free(mx->gnl);
		if (signal == END_OF_FILE)
			return ;
		mx->elem = ft_split(mx->line, ' ', &damy);
		if (!mx->elem)
			fdf_exit(d, "Failed to read map.");
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
