/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiroaki <hiroaki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 02:08:05 by hiroaki           #+#    #+#             */
/*   Updated: 2022/12/02 22:30:38 by hiroaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/fdf.h"

void	draw_line(t_data *d, t_pos p)
{
	t_pos	st;
	t_pos	cur;

	st = p;
	cur = p;
	if (cur.x != d->mx->width - 1)
	{
		st.x++;
		bresenham(d, reset_pos(d, cur), reset_pos(d, st));
		st.x--;
	}
	if (cur.y != d->mx->height - 1)
	{
		st.y++;
		bresenham(d, reset_pos(d, cur), reset_pos(d, st));
	}
}

void	draw_colored_line(t_mlx *mlx, t_pos cur)
{
	char	*dst;

	if (cur.x >= 0 && cur.y >= 0 && cur.x < SCR_WIDTH && cur.y < SCR_HEIGHT)
	{
		dst = \
		mlx->data_addr + (cur.x * mlx->bpp / 8) + (cur.y * mlx->size_line);
		*(unsigned int *)dst = cur.c.color;
	}
}

void	draw_bkg(t_mlx *mx)
{
	int	i;
	int	size;
	int	*img;

	size = SCR_WIDTH * SCR_HEIGHT * mx->bpp / 8;
	ft_bzero(mx->data_addr, size);
	img = (int *)mx->data_addr;
	i = -1;
	while (++i < SCR_WIDTH * SCR_HEIGHT)
		img[i] = NO_COLOR;
}
