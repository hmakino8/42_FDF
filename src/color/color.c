/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiroaki <hiroaki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 02:08:05 by hiroaki           #+#    #+#             */
/*   Updated: 2022/12/09 18:27:07 by hiroaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/fdf.h"

double	get_color_ratio(t_pos delta, t_pos st, t_pos cur, t_pos to)
{
	double	ratio;

	if (!(to.x - st.x) || !(to.y - st.y))
		return (1.0);
	if (delta.x > delta.y)
		ratio = (double)(cur.x - st.x) / (to.x - st.x);
	else
		ratio = (double)(cur.y - st.y) / (to.y - st.y);
	return (ratio);
}

t_pos	get_color(t_pos st, t_pos cur, t_pos to, double rt)
{
	int		sc;
	int		tc;
	double	a;

	sc = st.c.color;
	tc = to.c.color;
	if (cur.x <= MENU_WIDTH)
		a = 0.4;
	else
		a = 1;
	if (cur.c.color != to.c.color)
	{
		cur.c.red = ((sc >> 16 & 0xFF) * (1 - rt) + (tc >> 16 & 0xFF) * rt) * a;
		cur.c.green = ((sc >> 8 & 0xFF) * (1 - rt) + (tc >> 8 & 0xFF) * rt) * a;
		cur.c.blue = ((sc & 0xFF) * (1 - rt) + (tc & 0xFF) * rt) * a;
	}
	else
	{
		cur.c.red = (cur.c.color >> 16 & 0xFF) * a;
		cur.c.green = (cur.c.color >> 8 & 0xFF) * a;
		cur.c.blue = (cur.c.color & 0xFF) * a;
	}
	cur.c.color = (cur.c.red << 16 | (cur.c.green << 8) | cur.c.blue);
	return (cur);
}

static int	depth_gradation(t_pos p)
{
	if (p.z > 100)
		return (0xFFDF8D);
	if (p.z > 75)
		return (0xFFDE7A);
	if (p.z > 50)
		return (0xFFC568);
	if (p.z > 25)
		return (0xFD996B);
	if (p.z > 15)
		return (0xF7856C);
	if (p.z > 10)
		return (0xF06E6C);
	if (p.z > 5)
		return (0xD9576B);
	if (p.z > 0)
		return (0xA44369);
	if (p.z > -10)
		return (0x833F68);
	if (p.z > -20)
		return (0x833F68);
	if (p.z > -50)
		return (0x5E3C65);
	return (0x3F3A63);
}

t_pos	get_original_color(t_data *d, t_pos p)
{
	int		z_min;
	int		z_max;
	double	ratio;
	t_pos	top;
	t_pos	btm;

	z_max = d->mx->depth_max;
	z_min = d->mx->depth_min;
	top.c.color = DEEPPINK;
	btm.c.color = INDIGO;
	ratio = (double)(p.z - z_min) / (z_max - z_min);
	if (z_min > -20)
	{
		if (p.z == z_max)
			p.c.color = top.c.color;
		else if (p.z == z_min)
			p.c.color = btm.c.color;
		else
			p = get_color(btm, p, top, ratio);
	}
	else
		p.c.color = depth_gradation(p);
	return (p);
}

t_pos	get_menu_color(t_pos cur)
{
	double	ratio;

	if (cur.x <= MENU_WIDTH)
	{
		ratio = 0.3;
		cur.c.red *= ratio;
		cur.c.green *= ratio;
		cur.c.blue *= ratio;
		cur.c.color = (cur.c.red << 16 | (cur.c.green << 8) | cur.c.blue);
	}
	return (cur);
}
