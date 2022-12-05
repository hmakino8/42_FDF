/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiroaki <hiroaki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 02:08:05 by hiroaki           #+#    #+#             */
/*   Updated: 2022/12/05 21:05:46 by hiroaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/fdf.h"

void	check_argc(t_data *d, int argc)
{
	if (argc != 2)
		fdf_exit(d, "Invalid argument.");
}

void	check_width(t_data *d, t_matrix *mx, int *width)
{
	if (!*width)
		*width = mx->width;
	else if (mx->width != *width)
		fdf_exit(d, "Invalid width in map.");
}

int	check_z_axis(t_data *d, int z)
{
	if ((z > 0 && d->cam.zoom * d->cam.z_div <= INT_MAX / z) || \
		(z != 0 && z < -1 && d->cam.zoom * d->cam.z_div <= INT_MIN / z))
		return (z * d->cam.zoom * d->cam.z_div);
	return (z);
}

void	check_delta(t_data *d, t_pos delta)
{
	if (delta.x < 0 || delta.y < 0)
		stop_rendering(d, "Depth value too large to draw correctly.");
}

void	check_error(t_data *d, int error)
{
	if (error > INT_MAX / 2 || error < INT_MIN / 2)
		stop_rendering(d, "Depth value too large to draw correctly.");
}
