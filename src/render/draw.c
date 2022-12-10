/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiroaki <hiroaki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 02:08:05 by hiroaki           #+#    #+#             */
/*   Updated: 2022/12/10 16:10:56 by hiroaki          ###   ########.fr       */
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

static t_pos	color_transparency(t_pos cur)
{
	double	a;

	a = 0.4;
	cur.c.red = (cur.c.color >> 16 & 0xFF) * a;
	cur.c.green = (cur.c.color >> 8 & 0xFF) * a;
	cur.c.blue = (cur.c.color & 0xFF) * a;
	cur.c.color = (cur.c.red << 16 | (cur.c.green << 8) | cur.c.blue);
	return (cur);
}

void	draw_colored_line(t_mlx *mlx, t_pos cur)
{
	char	*dst;

	if (cur.x >= 0 && cur.y >= 0 && cur.x < SCR_WIDTH && cur.y < SCR_HEIGHT)
	{
		dst = \
		mlx->data_addr + (cur.x * mlx->bpp / 8) + (cur.y * mlx->size_line);
		if (cur.x <= MENU_WIDTH)
			cur = color_transparency(cur);
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
