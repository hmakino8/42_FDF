/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operation_key.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiroaki <hiroaki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 02:08:05 by hiroaki           #+#    #+#             */
/*   Updated: 2023/02/27 20:49:37 by hiroaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	zoom_key(t_camera *cam, int key)
{
	if (key == KEY_PLUS)
		cam->zoom++;
	if (cam->zoom > 1 && key == KEY_MINUS)
		cam->zoom--;
	return (0);
}

int	move_key(t_camera *cam, int key)
{
	if (key == KEY_H || key == KEY_LEFT)
		cam->x_et -= 10;
	if (key == KEY_J || key == KEY_DOWN)
		cam->y_et += 10;
	if (key == KEY_K || key == KEY_UP)
		cam->y_et -= 10;
	if (key == KEY_L || key == KEY_RIGHT)
		cam->x_et += 10;
	return (0);
}

int	rotate_key(t_camera *cam, int key)
{
	if (key == KEY_S)
		cam->alpha += 0.05;
	if (key == KEY_D)
		cam->beta += 0.05;
	if (key == KEY_F)
		cam->gamma += 0.05;
	if (key == KEY_W)
		cam->alpha -= 0.05;
	if (key == KEY_E)
		cam->beta -= 0.05;
	if (key == KEY_R)
		cam->gamma -= 0.05;
	return (0);
}

int	projection_key(t_camera *cam, t_matrix *mx, int key)
{
	if (key == KEY_P)
	{
		init_axis(cam);
		cam->projection = PARALLEL;
	}
	if (key == KEY_U)
	{
		init_axis(cam);
		cam->projection = INIT;
	}
	if (key == KEY_I)
		init_s_camera(cam, mx);
	return (0);
}

int	adjust_depth_key(t_camera *cam, int key)
{
	if (key == KEY_LESS)
		cam->z_div -= 0.1;
	if (key == KEY_GRATER)
		cam->z_div += 0.1;
	return (0);
}
