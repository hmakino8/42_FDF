/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiroaki <hiroaki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 02:08:05 by hiroaki           #+#    #+#             */
/*   Updated: 2022/12/02 22:33:10 by hiroaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/fdf.h"

static int	close_key(t_data *d)
{
	mlx_destroy_window(d->mlx->init, d->mlx->win);
	free_all_array(d->mx);
	free_all_struct(d);
	exit(EXIT_SUCCESS);
}

static int	on_keydown(int key, t_data *d)
{
	if (key == KEY_ESC)
		close_key(d);
	zoom_key(&d->cam, key);
	move_key(&d->cam, key);
	rotate_key(&d->cam, key);
	adjust_depth_key(&d->cam, key);
	projection_key(&d->cam, d->mx, key);
	rendering(d, d->mlx, d->mx);
	return (0);
}

void	key_hook(t_data *d, t_mlx *mlx)
{
	mlx_hook(mlx->win, 2, 0, on_keydown, d);
	mlx_hook(mlx->win, 17, 0, close_key, d);
}
