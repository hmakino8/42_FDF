/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_color_code.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiroaki <hiroaki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 02:08:05 by hiroaki           #+#    #+#             */
/*   Updated: 2022/12/10 17:22:24 by hiroaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/fdf.h"

void	get_color_code(t_data *d, t_matrix *mx, int i, int j)
{
	bool	ok;

	ok = false;
	if (mx->coord_infocnt == 1)
		mx->color[i][j] = -1;
	if (mx->coord_infocnt == 2)
		mx->color[i][j] = ft_atoi_base(mx->coord_info[1], 16, &ok);
	if (mx->coord_infocnt != 1 && \
		(!ok || mx->color[i][j] < 0x0 || mx->color[i][j] > 0xffffff))
		fdf_exit(d, "Invalid color code.");
}
