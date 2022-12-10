/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_coord_info.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiroaki <hiroaki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 02:08:05 by hiroaki           #+#    #+#             */
/*   Updated: 2022/12/10 17:20:19 by hiroaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/fdf.h"

static void	get_coord_info(t_data *d, t_matrix *mx, char *elem)
{
	mx->coord_info = ft_split(elem, ',', &mx->coord_infocnt);
	if (!mx->coord_info || mx->coord_infocnt > 2)
		fdf_exit(d, "Failed to read map.");
}

static bool	is_valid_depth(int max, int min)
{
	if (ft_abs(max, min) < 0)
		return (false);
	return (true);
}

void	parse_line(t_data *d, t_matrix *mx, int i)
{
	int	j;

	j = -1;
	while (mx->elem[++j])
	{
		get_coord_info(d, mx, mx->elem[j]);
		get_coord(d, mx, i, j);
		if (!is_valid_depth(mx->depth_max, mx->depth_min))
			fdf_exit(d, "Height difference in depth exceeds the range of int.");
		get_color_code(d, mx, i, j);
		free_all_element((void **)mx->coord_info, mx->coord_infocnt);
		mx->coord_info = NULL;
	}
	free_all_element((void **)mx->elem, j);
	mx->elem = NULL;
}
