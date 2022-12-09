/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiroaki <hiroaki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 02:08:05 by hiroaki           #+#    #+#             */
/*   Updated: 2022/12/07 02:26:05 by hiroaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/fdf.h"

static t_pos	relocate_pos(int error[], t_pos cur, t_pos delta, t_pos sign)
{
	error[1] = error[0] * 2;
	if (error[1] > -delta.y)
	{
		error[0] -= delta.y;
		cur.x += sign.x;
	}
	if (error[1] < delta.x)
	{
		error[0] += delta.x;
		cur.y += sign.y;
	}
	return (cur);
}

/*
 * Δx = |x`-x| => 次のpixelまでのx軸方向の距離
 * Δy = |y`-y| => 次のpixelまでのy軸方向の距離
 * k = Δy/Δx   => (x, y)から(x`, y`)の直線の傾き
 *
 *            error[i-1]+k       (error[i-1] < 0.5)
 * error[i] { error[i-1]+k-1     (error[i-1] >= 0.5) => 誤差(実数)
 *
 * 実数k,0.5を整数として扱いたいので両辺を2Δx倍(2Δx * error[i] => error[i]`)
 *             error[i-1]`+2Δy        (error[i-1]` >= Δx)
 * error[i]` { error[i-1]`+2Δy-2Δx    (error[i-1]` >= Δx) => 誤差(整数)
 */

void	bresenham(t_data *d, t_pos st, t_pos to)
{
	int		error[2];
	double	ratio;
	t_pos	cur;
	t_pos	delta;
	t_pos	sign;

	delta.x = ft_abs(to.x, st.x);
	delta.y = ft_abs(to.y, st.y);
	check_delta(d, delta);
	sign.x = (st.x < to.x) - (st.x >= to.x);
	sign.y = (st.y < to.y) - (st.y >= to.y);
	error[0] = delta.x - delta.y;
	cur = st;
	while (cur.x != to.x || cur.y != to.y)
	{
		ratio = get_color_ratio(delta, st, cur, to);
		cur = get_color(st, cur, to, ratio);
		draw_colored_line(d->mlx, cur);
		check_error(d, error[0]);
		cur = relocate_pos(error, cur, delta, sign);
	}
}

static t_pos	rotate(t_camera *cam, t_pos p)
{
	double	prev_x;
	double	prev_y;

	prev_y = p.y;
	p.y = prev_y * cos(cam->alpha) + p.z * sin(cam->alpha);
	p.z = -prev_y * sin(cam->alpha) + p.z * cos(cam->alpha);
	prev_x = p.x;
	p.x = prev_x * cos(cam->beta) + p.z * sin(cam->beta);
	p.z = -prev_x * sin(cam->beta) + p.z * cos(cam->beta);
	prev_x = p.x;
	prev_y = p.y;
	p.x = prev_x * cos(cam->gamma) - prev_y * sin(cam->gamma);
	p.y = prev_x * sin(cam->gamma) + prev_y * cos(cam->gamma);
	if (cam->projection == INIT)
	{
		prev_x = p.x;
		prev_y = p.y;
		p.x = (prev_x - prev_y) * cos(0.523599);
		p.y = -p.z + (prev_x + prev_y) * sin(0.523599);
	}
	return (p);
}

t_pos	reset_pos(t_data *d, t_pos p)
{
	p.c.color = d->mx->color[p.y][p.x];
	p.z = d->mx->coord[p.y][p.x];
	if (p.c.color < 0)
	{
		p.c.map_color = false;
		p = get_original_color(d, p);
	}
	else
		p.c.map_color = true;
	p.x *= d->cam.zoom;
	p.y *= d->cam.zoom;
	p.z = check_z_axis(d, p.z);
	p.x -= (d->mx->width * d->cam.zoom) / 2;
	p.y -= (d->mx->height * d->cam.zoom) / 2;
	p = rotate(&d->cam, p);
	p.x += SCR_WIDTH / 2 + d->cam.x_et;
	p.y += (SCR_HEIGHT + d->mx->height * d->cam.zoom) / 2 + d->cam.y_et;
	return (p);
}

void	rendering(t_data *d, t_mlx *mlx, t_matrix *mx)
{
	t_pos	p;

	draw_bkg(d->mlx);
	p.y = -1;
	while (++p.y < mx->height)
	{
		p.x = -1;
		while (++p.x < mx->width)
		{
			if (p.x != mx->width -1 || p.y != mx->height - 1)
				draw_line(d, p);
		}
	}
	mlx_put_image_to_window(mlx->init, mlx->win, mlx->img, 0, 0);
	put_menu(mlx);
}
