/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiroaki <hiroaki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 02:08:05 by hiroaki           #+#    #+#             */
/*   Updated: 2022/12/02 20:58:57 by hiroaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/fdf.h"

void	check_argc(t_data *d, int argc)
{
	if (argc < 2)
		fdf_exit(d, "Invalid argument.");
}

void	check_width(t_data *d, t_matrix *mx, int *width)
{
	if (!*width)
		*width = mx->width;
	else if (mx->width != *width)
		fdf_exit(d, "Invalid width in map.");
}
