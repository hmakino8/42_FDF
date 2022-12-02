/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_coord.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiroaki <hiroaki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 02:08:05 by hiroaki           #+#    #+#             */
/*   Updated: 2022/12/02 19:10:21 by hiroaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/fdf.h"

void	get_coord(t_data *d, t_matrix *mx, int i, int j)
{
	bool	ok;

	mx->coord[i][j] = ft_atoi_base(mx->coord_info[0], 10, &ok);
	if (!ok)
		fdf_exit(d, "Invalid map coord.");
	mx->depth_max = ft_max(mx->depth_max, mx->coord[i][j]);
	mx->depth_min = ft_min(mx->depth_min, mx->coord[i][j]);
}
