/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiroaki <hiroaki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 02:08:05 by hiroaki           #+#    #+#             */
/*   Updated: 2022/12/07 03:37:43 by hiroaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/fdf.h"

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
	//free_all_element((void **)mx->elem, mx->width);
	//free_all_element((void **)mx->coord_info, mx->coord_infocnt);
}

void	stop_rendering(t_data *d, char *errmsg)
{
	mlx_destroy_window(d->mlx->init, d->mlx->win);
	fdf_exit(d, errmsg);
}

int	fdf_exit(t_data *d, char *errmsg)
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
