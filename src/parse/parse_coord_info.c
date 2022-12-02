/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_coord_info.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiroaki <hiroaki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 02:08:05 by hiroaki           #+#    #+#             */
/*   Updated: 2022/12/02 19:12:07 by hiroaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/fdf.h"

static void	get_coord_info(t_data *d, t_matrix *mx, char *elem)
{
	mx->coord_info = ft_split(elem, ',', &mx->coord_infocnt);
	if (!mx->coord_info || mx->coord_infocnt > 2)
		fdf_exit(d, "Failed to read map.");
}

void	parse_line(t_data *d, t_matrix *mx, int i)
{
	int	j;

	j = -1;
	while (mx->elem[++j])
	{
		get_coord_info(d, mx, mx->elem[j]);
		get_coord(d, mx, i, j);
		get_color_code(d, mx, i, j);
		free_all_element((void **)mx->coord_info, mx->coord_infocnt);
		mx->coord_info = NULL;
	}
}
