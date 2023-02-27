/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiroaki <hiroaki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 02:08:05 by hiroaki           #+#    #+#             */
/*   Updated: 2023/02/27 20:49:11 by hiroaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
